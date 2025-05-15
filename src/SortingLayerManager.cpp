namespace playfultones
{
    SortingLayerManager::SortingLayerManager (juce::Component& componentToWrap)
        : component (componentToWrap)
    {
    }

    void SortingLayerManager::addAndMakeVisible (juce::Component& childComp, int layer)
    {
        component.addAndMakeVisible (childComp);
        setSortingLayer (childComp, layer);
    }

    void SortingLayerManager::addChildComponent (juce::Component& childComp, int layer)
    {
        component.addChildComponent (childComp);
        setSortingLayer (childComp, layer);
    }

    void SortingLayerManager::setSortingLayer (juce::Component& childComp, int layer)
    {
        componentLayers[&childComp] = layer;
        updateZOrder();
    }

    void SortingLayerManager::updateZOrder()
    {
        std::vector<std::pair<juce::Component*, int>> components;

        for (int i = 0; i < component.getNumChildComponents(); ++i)
        {
            auto* childComp = component.getChildComponent (i);
            auto it = componentLayers.find (childComp);

            if (it != componentLayers.end())
                components.emplace_back (childComp, it->second);
            else
                components.emplace_back (childComp, Layer::Default);
        }

        std::stable_sort (components.begin(), components.end(), [] (const auto& a, const auto& b) {
            // Lower layer order values should be toward the back (lower z-order)
            return a.second < b.second;
        });

        // Apply the sorted order to the actual components
        for (const auto& [comp, layer] : components)
            comp->toFront (false);
    }
} // namespace playfultones