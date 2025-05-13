#pragma once

namespace playfultones
{
    /**
     * Wrapper for a component that provides sorting layer functionality.
     */
    class SortingLayerManager
    {
    public:
        SortingLayerManager (juce::Component& componentToWrap);
        ~SortingLayerManager() = default;

        enum Layer {
            Background = 0,
            Default = 100,
            Menu = 2000,
            Popup = 3000,
            Licensing = 4000
        };

        // Wrapper for addAndMakeVisible with sorting layer support
        void addAndMakeVisible (juce::Component& childComp, int layer);

        // Wrapper for addChildComponent with sorting layer support
        void addChildComponent (juce::Component& childComp, int layer);

        // Sets the sorting layer for a component that's already a child
        void setSortingLayer (juce::Component& childComp, int layer);

    private:
        juce::Component& component;
        std::unordered_map<juce::Component*, int> componentLayers;
        void updateZOrder();
    };
} // namespace playfultones