#include "Patches/HookSelectedCategory.hpp"
#include "Patches/RestoreTableScroll.hpp"
#include "config.hpp"

#include "UI/FilterUI.hpp"

namespace BetterSongList::Hooks {
    GlobalNamespace::SelectLevelCategoryViewController::LevelCategory HookSelectedCategory::lastSelectedCategory = GlobalNamespace::SelectLevelCategoryViewController::LevelCategory::None;
    
    GlobalNamespace::SelectLevelCategoryViewController::LevelCategory HookSelectedCategory::get_lastSelectedCategory() {
        return lastSelectedCategory;
    }
    
    void HookSelectedCategory::SelectLevelCategoryViewController_LevelFilterCategoryIconSegmentedControlDidSelectCell_Prefix(GlobalNamespace::SelectLevelCategoryViewController* self) {
        if (lastSelectedCategory == self->get_selectedLevelCategory()) {
            return;
        }

        lastSelectedCategory = self->get_selectedLevelCategory();
        config.lastCategory = lastSelectedCategory;

        RestoreTableScroll::ResetScroll();

        auto instance = FilterUI::get_instance();
        instance->UpdateTransformerOptionsAndDropdowns();
    }
}