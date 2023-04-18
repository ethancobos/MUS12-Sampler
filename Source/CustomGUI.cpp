/*
  ==============================================================================

    CustomGUI.cpp
    Created: 16 Apr 2023 11:23:41pm
    Author:  Ethan Cobos

  ==============================================================================
*/

#include "CustomGUI.h"

namespace juce {

CustomGUI::CustomGUI()
{
    applyThreeColourScheme(Colour(0xFFA1BD).withAlpha(1.0f), Colour(0xA69888).withAlpha(1.0f), Colour(0x6B6D76).withAlpha(1.0f));
}

inline void CustomGUI::applyThreeColourScheme(Colour accentBaseColour, Colour foregroundBaseColour, Colour backgroundBaseColour)
{
    auto fg = foregroundBaseColour.getARGB();
    auto bright = foregroundBaseColour.withMultipliedBrightness(1.5f).getARGB();
    auto dim = foregroundBaseColour.withMultipliedBrightness(0.6f).getARGB();
    auto bg = backgroundBaseColour.getARGB();
    auto accent = accentBaseColour.getARGB();
    auto transparent = Colours::transparentBlack.getARGB();
    auto black = Colours::black.getARGB();

    static const juce::uint32 standardColours[] =
    {
        TextButton::buttonColourId,                 fg,
        TextButton::buttonOnColourId,               accent,
        TextButton::textColourOnId,                 bg,
        TextButton::textColourOffId,                bg,

        ToggleButton::textColourId,                 fg,

        TextEditor::backgroundColourId,             bg,
        TextEditor::textColourId,                   fg,
        TextEditor::highlightColourId,              bg,
        TextEditor::highlightedTextColourId,        fg,
        TextEditor::outlineColourId,                transparent,
        TextEditor::focusedOutlineColourId,         fg,
        TextEditor::shadowColourId,                 transparent,

        CaretComponent::caretColourId,              fg,

        Label::backgroundColourId,                  transparent,
        Label::textColourId,                        fg,
        Label::outlineColourId,                     transparent,

        ScrollBar::backgroundColourId,              transparent,
        ScrollBar::thumbColourId,                   fg,

        TreeView::linesColourId,                    dim,
        TreeView::backgroundColourId,               transparent,
        TreeView::dragAndDropIndicatorColourId,     accent,
        TreeView::selectedItemBackgroundColourId,   fg,

        PopupMenu::backgroundColourId,              bg,
        PopupMenu::textColourId,                    fg,
        PopupMenu::headerTextColourId,              bright,
        PopupMenu::highlightedTextColourId,         bg,
        PopupMenu::highlightedBackgroundColourId,   accent,

        ComboBox::buttonColourId,                   fg,
        ComboBox::outlineColourId,                  dim,
        ComboBox::textColourId,                     fg,
        ComboBox::backgroundColourId,               bg,
        ComboBox::arrowColourId,                    fg,

        PropertyComponent::backgroundColourId,      bg,
        PropertyComponent::labelTextColourId,       fg,

        TextPropertyComponent::backgroundColourId,  bg,
        TextPropertyComponent::textColourId,        fg,
        TextPropertyComponent::outlineColourId,     dim,

        BooleanPropertyComponent::backgroundColourId, bg,
        BooleanPropertyComponent::outlineColourId,  dim,

        ListBox::backgroundColourId,                bg,
        ListBox::outlineColourId,                   fg,
        ListBox::textColourId,                      fg,

        Slider::backgroundColourId,                 transparent,
        Slider::thumbColourId,                      fg,
        Slider::trackColourId,                      accent,
        Slider::rotarySliderFillColourId,           accent,
        Slider::rotarySliderOutlineColourId,        black,
        Slider::textBoxTextColourId,                fg,
        Slider::textBoxBackgroundColourId,          bg,
        Slider::textBoxHighlightColourId,           bright,
        Slider::textBoxOutlineColourId,             dim,

        ResizableWindow::backgroundColourId,        bg,
        //DocumentWindow::textColourId,               0xff000000, // (this is deliberately not set)

        AlertWindow::backgroundColourId,            bg,
        AlertWindow::textColourId,                  fg,
        AlertWindow::outlineColourId,               accent,

        ProgressBar::backgroundColourId,            bg,
        ProgressBar::foregroundColourId,            accent,

        TooltipWindow::backgroundColourId,          bg,
        TooltipWindow::textColourId,                fg,
        TooltipWindow::outlineColourId,             dim,

        TabbedComponent::backgroundColourId,        transparent,
        TabbedComponent::outlineColourId,           dim,
        TabbedButtonBar::tabOutlineColourId,        dim,
        TabbedButtonBar::frontOutlineColourId,      fg,

        Toolbar::backgroundColourId,                bg,
        Toolbar::separatorColourId,                 fg,
        Toolbar::buttonMouseOverBackgroundColourId, accent,
        Toolbar::buttonMouseDownBackgroundColourId, bg,
        Toolbar::labelTextColourId,                 fg,
        Toolbar::editingModeOutlineColourId,        accent,

        DrawableButton::textColourId,               fg,
        DrawableButton::textColourOnId,             bg,
        DrawableButton::backgroundColourId,         bg,
        DrawableButton::backgroundOnColourId,       accent,

        HyperlinkButton::textColourId,              accent,

        GroupComponent::outlineColourId,            0x66000000,
        GroupComponent::textColourId,               0xff000000,

        BubbleComponent::backgroundColourId,        0xeeeeeebb,
        BubbleComponent::outlineColourId,           0x77000000,

        DirectoryContentsDisplayComponent::highlightColourId,   accent,
        DirectoryContentsDisplayComponent::textColourId,        fg,

        0x1000440, /*LassoComponent::lassoFillColourId*/        transparent,
        0x1000441, /*LassoComponent::lassoOutlineColourId*/     accent,

        0x1005000, /*MidiKeyboardComponent::whiteNoteColourId*/               bg,
        0x1005001, /*MidiKeyboardComponent::blackNoteColourId*/               fg,
        0x1005002, /*MidiKeyboardComponent::keySeparatorLineColourId*/        dim,
        0x1005003, /*MidiKeyboardComponent::mouseOverKeyOverlayColourId*/     accent,
        0x1005004, /*MidiKeyboardComponent::keyDownOverlayColourId*/          dim,
        0x1005005, /*MidiKeyboardComponent::textLabelColourId*/               fg,
        0x1005006, /*MidiKeyboardComponent::upDownButtonBackgroundColourId*/  fg,
        0x1005007, /*MidiKeyboardComponent::upDownButtonArrowColourId*/       bg,
        0x1005008, /*MidiKeyboardComponent::shadowColourId*/                  transparent,

        0x1004500, /*CodeEditorComponent::backgroundColourId*/                bg,
        0x1004502, /*CodeEditorComponent::highlightColourId*/                 dim,
        0x1004503, /*CodeEditorComponent::defaultTextColourId*/               fg,
        0x1004504, /*CodeEditorComponent::lineNumberBackgroundId*/            bg,
        0x1004505, /*CodeEditorComponent::lineNumberTextId*/                  dim,

        0x1007000, /*ColourSelector::backgroundColourId*/                     bg,
        0x1007001, /*ColourSelector::labelTextColourId*/                      fg,

        0x100ad00, /*KeyMappingEditorComponent::backgroundColourId*/          bg,
        0x100ad01, /*KeyMappingEditorComponent::textColourId*/                fg,

        FileSearchPathListComponent::backgroundColourId,        bg,

        FileChooserDialogBox::titleTextColourId,                fg,
    };

    for (int i = 0; i < numElementsInArray(standardColours); i += 2)
        setColour(int(standardColours[i]), Colour(juce::uint32(standardColours[i + 1])));
}


void CustomGUI::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    auto outline = slider.findColour (Slider::rotarySliderOutlineColourId);
    auto fill    = slider.findColour (Slider::rotarySliderFillColourId);
    
    auto bounds = Rectangle<int> (x, y, width, height).toFloat().reduced (10);
    
    auto radius = jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = jmin (8.0f, radius * 0.1f);
    auto arcRadius = radius - lineW * 0.5f;
    
    Path backgroundArc;
    backgroundArc.addCentredArc (bounds.getCentreX(),
                                 bounds.getCentreY(),
                                 arcRadius,
                                 arcRadius,
                                 0.0f,
                                 rotaryStartAngle,
                                 rotaryEndAngle,
                                 true);
    
    g.setColour (outline);
    g.strokePath (backgroundArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));
    
    if (slider.isEnabled())
    {
        Path valueArc;
        valueArc.addCentredArc (bounds.getCentreX(),
                                bounds.getCentreY(),
                                arcRadius,
                                arcRadius,
                                0.0f,
                                rotaryStartAngle,
                                toAngle,
                                true);
        
        g.setColour (fill);
        g.strokePath (valueArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));
    }
    
    Point<float> thumbPoint (bounds.getCentreX() + (arcRadius - lineW) * std::cos (toAngle - MathConstants<float>::halfPi),
                             bounds.getCentreY() + (arcRadius - lineW) * std::sin (toAngle - MathConstants<float>::halfPi));
    
    g.setColour (slider.findColour (Slider::rotarySliderFillColourId));
    g.drawLine(backgroundArc.getBounds().getCentreX(), backgroundArc.getBounds().getCentreY(), thumbPoint.getX(), thumbPoint.getY(), lineW);
}

}
