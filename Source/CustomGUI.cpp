/*
  ==============================================================================

    CustomGUI.cpp
    Created: 16 Apr 2023 11:23:41pm
    Author:  Ethan Cobos

  ==============================================================================
*/

#include "CustomGUI.h"

namespace juce {

const Colour CustomGUI::accentC = Colour(0xFFA1BD).withAlpha(1.0f);
const Colour CustomGUI::textC = Colour(0xE8DDB5).withAlpha(1.0f);
const Colour CustomGUI::backgroundC = Colour(0x456990).withAlpha(1.0f);
const Colour CustomGUI::foregroundC = Colour(0x558B6E).withAlpha(1.0f);

CustomGUI::CustomGUI()
{
    applyThreeColourScheme();
}

inline void CustomGUI::applyThreeColourScheme()
{
    auto fg = foregroundC.getARGB();
    auto bright = foregroundC.withMultipliedBrightness(1.5f).getARGB();
    auto dim = foregroundC.withMultipliedBrightness(0.6f).getARGB();
    auto bg = backgroundC.getARGB();
    auto accent = accentC.getARGB();
    auto transparent = Colours::transparentBlack.getARGB();
    auto black = Colours::black.getARGB();
    auto text = textC.getARGB();

    static const juce::uint32 standardColours[] =
    {
        TextButton::buttonColourId,                 fg,
        TextButton::buttonOnColourId,               accent,
        TextButton::textColourOnId,                 bg,
        TextButton::textColourOffId,                bg,

        ToggleButton::textColourId,                 text,
        ToggleButton::tickDisabledColourId,         black,
        ToggleButton::tickColourId,                 accent,

        TextEditor::backgroundColourId,             bg,
        TextEditor::textColourId,                   fg,
        TextEditor::highlightColourId,              bg,
        TextEditor::highlightedTextColourId,        fg,
        TextEditor::outlineColourId,                transparent,
        TextEditor::focusedOutlineColourId,         fg,
        TextEditor::shadowColourId,                 transparent,

        CaretComponent::caretColourId,              fg,

        Label::backgroundColourId,                  transparent,
        Label::textColourId,                        text,
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
        Slider::thumbColourId,                      bg,
        Slider::trackColourId,                      accent,
        Slider::rotarySliderFillColourId,           accent,
        Slider::rotarySliderOutlineColourId,        black,
        Slider::textBoxTextColourId,                text,
        Slider::textBoxBackgroundColourId,          bg,
        Slider::textBoxHighlightColourId,           bright,
        Slider::textBoxOutlineColourId,             transparent,

        ResizableWindow::backgroundColourId,        bg,
//        DocumentWindow::textColourId,               text, // (this is deliberately not set)

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

        
        // DONT CHANGE THESE
        Toolbar::backgroundColourId,                bg,
        Toolbar::separatorColourId,                 fg,
        Toolbar::buttonMouseOverBackgroundColourId, dim,
        Toolbar::buttonMouseDownBackgroundColourId, accent,
        Toolbar::labelTextColourId,                 text,
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

void CustomGUI::drawToggleButton (Graphics& g, ToggleButton& button,
                                       bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    auto fontSize = jmin (15.0f, (float) button.getHeight() * 0.75f);
    auto tickWidth = fontSize * 1.1f;
    
    Rectangle<float> tickBounds (1.0f, 1.0f, button.getWidth() - 2.0f, button.getHeight() - 2.0f);

    g.setColour (button.findColour (ToggleButton::tickDisabledColourId));
    g.fillRoundedRectangle (tickBounds, 4.0f);
    g.setColour (button.findColour (Toolbar::separatorColourId));
    g.drawRoundedRectangle (tickBounds, 4.0f, 2.0f);

    if (button.getToggleState())
    {
        g.setColour (button.findColour (ToggleButton::tickColourId));
        g.fillRoundedRectangle (tickBounds, 4.0f);
        g.setColour (button.findColour (Toolbar::separatorColourId));
        g.drawRoundedRectangle (tickBounds, 4.0f, 2.0f);
    }
    
    g.setColour (button.findColour (ToggleButton::textColourId));
    g.setFont (fontSize);

    if (! button.isEnabled())
        g.setOpacity (0.5f);

    g.drawFittedText (button.getButtonText(),
                      button.getLocalBounds().withTrimmedLeft (roundToInt (tickWidth) + 10)
                                             .withTrimmedRight (2),
                      Justification::centredLeft, 10);
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
    g.strokePath (backgroundArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::square));
    
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
        g.strokePath (valueArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::square));
    }
    
    Point<float> thumbPoint (bounds.getCentreX() + (arcRadius - lineW) * std::cos (toAngle - MathConstants<float>::halfPi),
                             bounds.getCentreY() + (arcRadius - lineW) * std::sin (toAngle - MathConstants<float>::halfPi));
    
    g.setColour (slider.findColour (Slider::rotarySliderFillColourId));
    g.drawLine(backgroundArc.getBounds().getCentreX(), backgroundArc.getBounds().getCentreY(), thumbPoint.getX(), thumbPoint.getY(), lineW);
    g.fillEllipse(backgroundArc.getBounds().getCentreX() - (lineW / 2), backgroundArc.getBounds().getCentreY() - (lineW / 2), lineW, lineW);
}

void CustomGUI::drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                                       float sliderPos,
                                       float minSliderPos,
                                       float maxSliderPos,
                                       const Slider::SliderStyle style, Slider& slider)
{
    if (slider.isBar())
    {
        g.setColour (slider.findColour (Slider::trackColourId));
        g.fillRect (slider.isHorizontal() ? Rectangle<float> (static_cast<float> (x), (float) y + 0.5f, sliderPos - (float) x, (float) height - 1.0f)
                                          : Rectangle<float> ((float) x + 0.5f, sliderPos, (float) width - 1.0f, (float) y + ((float) height - sliderPos)));
    }
    else
    {
        auto isTwoVal   = (style == Slider::SliderStyle::TwoValueVertical   || style == Slider::SliderStyle::TwoValueHorizontal);
        auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

        auto trackWidth = jmin (6.0f, slider.isHorizontal() ? (float) height * 0.25f : (float) width * 0.25f);

        Point<float> startPoint (slider.isHorizontal() ? (float) x : (float) x + (float) width * 0.5f,
                                 slider.isHorizontal() ? (float) y + (float) height * 0.5f : (float) (height + y));

        Point<float> endPoint (slider.isHorizontal() ? (float) (width + x) : startPoint.x,
                               slider.isHorizontal() ? startPoint.y : (float) y);

        Path backgroundTrack;
        backgroundTrack.startNewSubPath (startPoint);
        backgroundTrack.lineTo (endPoint);
        g.setColour (Colours::black);
        g.strokePath (backgroundTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

        Path valueTrack;
        Point<float> minPoint, maxPoint, thumbPoint;

        if (isTwoVal || isThreeVal)
        {
            minPoint = { slider.isHorizontal() ? minSliderPos : (float) width * 0.5f,
                         slider.isHorizontal() ? (float) height * 0.5f : minSliderPos };

            if (isThreeVal)
                thumbPoint = { slider.isHorizontal() ? sliderPos : (float) width * 0.5f,
                               slider.isHorizontal() ? (float) height * 0.5f : sliderPos };

            maxPoint = { slider.isHorizontal() ? maxSliderPos : (float) width * 0.5f,
                         slider.isHorizontal() ? (float) height * 0.5f : maxSliderPos };
        }
        else
        {
            auto kx = slider.isHorizontal() ? sliderPos : ((float) x + (float) width * 0.5f);
            auto ky = slider.isHorizontal() ? ((float) y + (float) height * 0.5f) : sliderPos;

            minPoint = startPoint;
            maxPoint = { kx, ky };
        }

        auto thumbWidth = getSliderThumbRadius (slider);

        valueTrack.startNewSubPath (minPoint);
        valueTrack.lineTo (isThreeVal ? thumbPoint : maxPoint);
        g.setColour (slider.findColour (Slider::trackColourId));
        g.strokePath (valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

        if (! isTwoVal)
        {
            g.setColour (slider.findColour (Slider::thumbColourId));
            g.fillEllipse (Rectangle<float> (static_cast<float> (thumbWidth), static_cast<float> (thumbWidth)).withCentre (isThreeVal ? thumbPoint : maxPoint));
        }

        if (isTwoVal || isThreeVal)
        {
            auto sr = jmin (trackWidth, (slider.isHorizontal() ? (float) height : (float) width) * 0.4f);
            auto pointerColour = slider.findColour (Slider::thumbColourId);

            if (slider.isHorizontal())
            {
                drawPointer (g, minSliderPos - sr,
                             jmax (0.0f, (float) y + (float) height * 0.5f - trackWidth * 2.0f),
                             trackWidth * 2.0f, pointerColour, 2);

                drawPointer (g, maxSliderPos - trackWidth,
                             jmin ((float) (y + height) - trackWidth * 2.0f, (float) y + (float) height * 0.5f),
                             trackWidth * 2.0f, pointerColour, 4);
            }
            else
            {
                drawPointer (g, jmax (0.0f, (float) x + (float) width * 0.5f - trackWidth * 2.0f),
                             minSliderPos - trackWidth,
                             trackWidth * 2.0f, pointerColour, 1);

                drawPointer (g, jmin ((float) (x + width) - trackWidth * 2.0f, (float) x + (float) width * 0.5f), maxSliderPos - sr,
                             trackWidth * 2.0f, pointerColour, 3);
            }
        }
    }
}


}
