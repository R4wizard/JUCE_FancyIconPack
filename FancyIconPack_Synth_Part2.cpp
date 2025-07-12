#include "FancyIconPack.h"

// ============================================================================
// SYNTH AND FX COMPONENTS IMPLEMENTATION - PART 2
// ============================================================================

// Envelopes and LFOs
// ============================================================================

void FancyIconPack::drawEnv1(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Envelope curve area
    auto envelopeArea = iconBounds.removeFromTop(iconBounds.getHeight() * 0.6f);

    // ADSR envelope shape
    juce::Path envelope;
    auto baseY = envelopeArea.getBottom();
    auto startX = envelopeArea.getX();
    auto width = envelopeArea.getWidth();
    auto height = envelopeArea.getHeight() * 0.9f;

    envelope.startNewSubPath(startX, baseY);

    // Attack
    envelope.lineTo(startX + width * 0.25f, baseY - height);
    // Decay
    envelope.lineTo(startX + width * 0.45f, baseY - height * 0.65f);
    // Sustain
    envelope.lineTo(startX + width * 0.7f, baseY - height * 0.65f);
    // Release
    envelope.lineTo(startX + width, baseY);

    g.setColour(color);
    g.strokePath(envelope, createStroke(stroke));

    // "ENV1" label
    auto labelArea = iconBounds.removeFromBottom(iconBounds.getHeight());
    g.setFont(juce::Font(labelArea.getHeight() * 0.6f, juce::Font::bold));
    g.drawText("ENV1", labelArea, juce::Justification::centred);
}

void FancyIconPack::drawEnv2(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // ADSR envelope curve (similar to drawEnv1 but with different styling)
    auto envelopeArea = iconBounds.removeFromTop(iconBounds.getHeight() * 0.6f);

    juce::Path adsrCurve;
    auto baseY = envelopeArea.getBottom();
    auto peakY = envelopeArea.getY() + envelopeArea.getHeight() * 0.1f;
    auto sustainY = envelopeArea.getY() + envelopeArea.getHeight() * 0.4f;

    auto attackX = envelopeArea.getX() + envelopeArea.getWidth() * 0.15f;
    auto decayX = envelopeArea.getX() + envelopeArea.getWidth() * 0.35f;
    auto sustainStartX = envelopeArea.getX() + envelopeArea.getWidth() * 0.4f;
    auto sustainEndX = envelopeArea.getX() + envelopeArea.getWidth() * 0.75f;
    auto releaseX = envelopeArea.getRight();

    // Draw ADSR curve with different color styling
    adsrCurve.startNewSubPath(envelopeArea.getX(), baseY);
    adsrCurve.lineTo(attackX, peakY);        // Attack
    adsrCurve.lineTo(decayX, sustainY);      // Decay
    adsrCurve.lineTo(sustainStartX, sustainY); // Sustain start
    adsrCurve.lineTo(sustainEndX, sustainY);   // Sustain hold
    adsrCurve.lineTo(releaseX, baseY);       // Release

    g.setColour(color);
    g.strokePath(adsrCurve, createStroke(stroke * 1.2f));

    // Stage indicators (different from ENV1)
    g.setColour(color.withAlpha(0.6f));
    g.setFont(juce::Font(envelopeArea.getHeight() * 0.12f, juce::Font::bold));

    // Attack indicator
    g.drawText("A", juce::Rectangle<float>(envelopeArea.getX(), peakY - stroke * 3.0f,
                                         attackX - envelopeArea.getX(), stroke * 3.0f),
               juce::Justification::centred);

    // Decay indicator
    g.drawText("D", juce::Rectangle<float>(attackX, sustainY - stroke * 2.0f,
                                         decayX - attackX, stroke * 2.0f),
               juce::Justification::centred);

    // "ENV2" label with different styling
    auto labelArea = iconBounds.removeFromBottom(iconBounds.getHeight());
    g.setColour(color);
    g.setFont(juce::Font(labelArea.getHeight() * 0.7f, juce::Font::bold));
    g.drawText("2", labelArea, juce::Justification::centred);

    // Small "ENV" text
    g.setFont(juce::Font(labelArea.getHeight() * 0.4f));
    g.drawText("ENV", juce::Rectangle<float>(labelArea.getX(), labelArea.getY() - labelArea.getHeight() * 0.2f,
                                           labelArea.getWidth(), labelArea.getHeight() * 0.4f),
               juce::Justification::centred);
}

void FancyIconPack::drawLFO1(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // LFO waveform area
    auto waveArea = iconBounds.removeFromTop(iconBounds.getHeight() * 0.6f);

    // Sine wave (typical LFO shape)
    juce::Path lfoWave;
    auto waveY = waveArea.getCentreY();
    auto amplitude = waveArea.getHeight() * 0.35f;
    auto points = 16;

    lfoWave.startNewSubPath(waveArea.getX(), waveY);

    for (int i = 1; i <= points; ++i)
    {
        auto x = waveArea.getX() + (i / static_cast<float>(points)) * waveArea.getWidth();
        auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 1.0f;
        auto amp = std::sin(phase) * amplitude;
        lfoWave.lineTo(x, waveY + amp);
    }

    g.setColour(color);
    g.strokePath(lfoWave, createStroke(stroke));

    // Rate indicators (small arrows)
    auto arrowY = waveArea.getBottom() + iconBounds.getHeight() * 0.05f;
    auto arrowSpacing = waveArea.getWidth() * 0.25f;

    g.setColour(color.withAlpha(0.6f));
    for (int i = 0; i < 4; ++i)
    {
        auto arrowX = waveArea.getX() + arrowSpacing * i + arrowSpacing * 0.2f;
        auto arrowSize = iconBounds.getWidth() * 0.03f;

        juce::Path arrow;
        arrow.startNewSubPath(arrowX, arrowY);
        arrow.lineTo(arrowX + arrowSize, arrowY - arrowSize * 0.5f);
        arrow.lineTo(arrowX + arrowSize, arrowY + arrowSize * 0.5f);
        arrow.closeSubPath();

        g.fillPath(arrow);
    }

    // "LFO1" label
    auto labelArea = iconBounds.removeFromBottom(iconBounds.getHeight());
    g.setColour(color);
    g.setFont(juce::Font(labelArea.getHeight() * 0.6f, juce::Font::bold));
    g.drawText("LFO1", labelArea, juce::Justification::centred);
}

void FancyIconPack::drawLFO2(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // LFO waveform area (triangle wave for LFO2)
    auto waveArea = iconBounds.removeFromTop(iconBounds.getHeight() * 0.6f);

    // Triangle wave pattern
    juce::Path lfoWave;
    auto waveY = waveArea.getCentreY();
    auto amplitude = waveArea.getHeight() * 0.35f;
    auto cycleWidth = waveArea.getWidth() / 2.0f;

    lfoWave.startNewSubPath(waveArea.getX(), waveY);

    for (int i = 0; i < 2; ++i)
    {
        auto cycleStart = waveArea.getX() + i * cycleWidth;
        auto quarterCycle = cycleWidth * 0.25f;

        // Rising edge
        lfoWave.lineTo(cycleStart + quarterCycle, waveY - amplitude);
        lfoWave.lineTo(cycleStart + quarterCycle * 3.0f, waveY + amplitude);
        lfoWave.lineTo(cycleStart + cycleWidth, waveY);
    }

    g.setColour(color);
    g.strokePath(lfoWave, createStroke(stroke));

    // Oscillation direction arrows (different pattern from LFO1)
    g.setColour(color.withAlpha(0.6f));
    auto arrowY = waveArea.getBottom() + stroke * 2.0f;
    auto arrowSpacing = waveArea.getWidth() / 3.0f;

    for (int i = 0; i < 3; ++i)
    {
        auto arrowX = waveArea.getX() + arrowSpacing * i + arrowSpacing * 0.3f;
        auto arrowSize = iconBounds.getWidth() * 0.025f;

        // Alternating up/down arrows for triangle pattern
        auto direction = (i % 2 == 0) ? 1.0f : -1.0f;

        juce::Path arrow;
        arrow.startNewSubPath(arrowX, arrowY);
        arrow.lineTo(arrowX - arrowSize * 0.5f, arrowY + direction * arrowSize);
        arrow.lineTo(arrowX + arrowSize * 0.5f, arrowY + direction * arrowSize);
        arrow.closeSubPath();

        g.fillPath(arrow);
    }

    // "LFO2" label
    auto labelArea = iconBounds.removeFromBottom(iconBounds.getHeight());
    g.setColour(color);
    g.setFont(juce::Font(labelArea.getHeight() * 0.6f, juce::Font::bold));
    g.drawText("LFO2", labelArea, juce::Justification::centred);
}

void FancyIconPack::drawLFO3(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // LFO waveform area (square wave for LFO3)
    auto waveArea = iconBounds.removeFromTop(iconBounds.getHeight() * 0.6f);

    // Square wave pattern
    juce::Path lfoWave;
    auto waveY = waveArea.getCentreY();
    auto amplitude = waveArea.getHeight() * 0.35f;
    auto cycleWidth = waveArea.getWidth() / 2.0f;

    lfoWave.startNewSubPath(waveArea.getX(), waveY + amplitude);

    for (int i = 0; i < 2; ++i)
    {
        auto cycleStart = waveArea.getX() + i * cycleWidth;
        auto halfCycle = cycleWidth * 0.5f;

        // High part
        lfoWave.lineTo(cycleStart, waveY + amplitude);
        lfoWave.lineTo(cycleStart, waveY - amplitude);
        lfoWave.lineTo(cycleStart + halfCycle, waveY - amplitude);

        // Low part
        lfoWave.lineTo(cycleStart + halfCycle, waveY + amplitude);
        lfoWave.lineTo(cycleStart + cycleWidth, waveY + amplitude);
    }

    g.setColour(color);
    g.strokePath(lfoWave, createStroke(stroke, juce::PathStrokeType::mitered, juce::PathStrokeType::butt));

    // Digital/stepped indicators (dots for square wave)
    g.setColour(color.withAlpha(0.6f));
    auto dotY = waveArea.getBottom() + stroke * 1.5f;
    auto numDots = 4;

    for (int i = 0; i < numDots; ++i)
    {
        auto dotX = waveArea.getX() + (i + 0.5f) * (waveArea.getWidth() / numDots);
        auto dotSize = stroke * 1.2f;

        g.fillEllipse(dotX - dotSize * 0.5f, dotY - dotSize * 0.5f, dotSize, dotSize);
    }

    // "LFO3" label
    auto labelArea = iconBounds.removeFromBottom(iconBounds.getHeight());
    g.setColour(color);
    g.setFont(juce::Font(labelArea.getHeight() * 0.6f, juce::Font::bold));
    g.drawText("LFO3", labelArea, juce::Justification::centred);
}

// Effects Chain
// ============================================================================

void FancyIconPack::drawFX(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Generic effects processing symbol - signal transformation
    auto center = iconBounds.getCentre();
    auto radius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.35f;

    // Central processing unit (hexagon)
    juce::Path processor;
    auto numSides = 6;

    for (int i = 0; i < numSides; ++i)
    {
        auto angle = (i / float(numSides)) * 2.0f * juce::MathConstants<float>::pi - juce::MathConstants<float>::pi * 0.5f;
        auto x = center.x + std::cos(angle) * radius;
        auto y = center.y + std::sin(angle) * radius;

        if (i == 0)
            processor.startNewSubPath(x, y);
        else
            processor.lineTo(x, y);
    }
    processor.closeSubPath();

    g.setColour(color.withAlpha(0.3f));
    g.fillPath(processor);
    g.setColour(color);
    g.strokePath(processor, createStroke(stroke));

    // Input and output signal flows
    auto inputX = iconBounds.getX() + stroke;
    auto outputX = iconBounds.getRight() - stroke;
    auto signalY = center.y;

    // Input signal (straight line)
    g.setColour(color.withAlpha(0.7f));
    g.drawLine(inputX, signalY, center.x - radius * 1.1f, signalY, stroke);

    // Output signal (modified/processed)
    juce::Path outputSignal;
    outputSignal.startNewSubPath(center.x + radius * 1.1f, signalY);

    auto outputWidth = outputX - (center.x + radius * 1.1f);
    for (int i = 0; i <= 10; ++i)
    {
        auto x = center.x + radius * 1.1f + (i / 10.0f) * outputWidth;
        auto y = signalY + std::sin(i * 0.8f) * stroke * 1.5f; // Processed/modulated signal
        outputSignal.lineTo(x, y);
    }

    g.strokePath(outputSignal, createStroke(stroke * 0.8f));

    // "FX" label in center
    g.setColour(color);
    g.setFont(juce::Font(radius * 0.6f, juce::Font::bold));
    g.drawText("FX", juce::Rectangle<float>(center.x - radius * 0.5f, center.y - radius * 0.3f,
                                          radius, radius * 0.6f),
               juce::Justification::centred);
}

void FancyIconPack::drawFXChain(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Chain of effect boxes connected by signal flow
    auto numEffects = 3;
    auto effectWidth = iconBounds.getWidth() / (numEffects + 1);
    auto effectHeight = iconBounds.getHeight() * 0.4f;
    auto effectY = iconBounds.getY() + (iconBounds.getHeight() - effectHeight) * 0.5f;

    for (int i = 0; i < numEffects; ++i)
    {
        auto effectX = iconBounds.getX() + (i + 0.5f) * effectWidth;
        auto effectRect = juce::Rectangle<float>(effectX - effectWidth * 0.3f, effectY,
                                               effectWidth * 0.6f, effectHeight);

        // Effect box
        g.setColour(color.withAlpha(0.3f));
        g.fillRoundedRectangle(effectRect, stroke);
        g.setColour(color);
        g.drawRoundedRectangle(effectRect, stroke, stroke * 0.7f);

        // Effect type indicators
        g.setFont(juce::Font(effectHeight * 0.25f, juce::Font::bold));
        juce::String effectNames[] = {"EQ", "DLY", "RVB"};
        g.drawText(effectNames[i], effectRect, juce::Justification::centred);

        // Connection arrows between effects
        if (i < numEffects - 1)
        {
            auto arrowStart = effectRect.getRight() + stroke;
            auto arrowEnd = effectX + effectWidth * 0.2f;
            auto arrowY = effectRect.getCentreY();

            g.setColour(color.withAlpha(0.7f));
            g.drawLine(arrowStart, arrowY, arrowEnd, arrowY, stroke * 0.8f);

            // Arrow head
            juce::Path arrowHead;
            arrowHead.startNewSubPath(arrowEnd, arrowY);
            arrowHead.lineTo(arrowEnd - stroke * 1.5f, arrowY - stroke);
            arrowHead.lineTo(arrowEnd - stroke * 1.5f, arrowY + stroke);
            arrowHead.closeSubPath();

            g.fillPath(arrowHead);
        }
    }

    // Input/output indicators
    g.setColour(color.withAlpha(0.6f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.12f));

    // Input
    g.drawText("IN", juce::Rectangle<float>(iconBounds.getX(), iconBounds.getY(),
                                          effectWidth * 0.4f, iconBounds.getHeight() * 0.2f),
               juce::Justification::centred);

    // Output
    g.drawText("OUT", juce::Rectangle<float>(iconBounds.getRight() - effectWidth * 0.4f,
                                           iconBounds.getBottom() - iconBounds.getHeight() * 0.2f,
                                           effectWidth * 0.4f, iconBounds.getHeight() * 0.2f),
               juce::Justification::centred);
}

void FancyIconPack::drawFXSlot(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Empty effect slot placeholder
    auto slotRect = iconBounds.reduced(iconBounds.getWidth() * 0.1f, iconBounds.getHeight() * 0.2f);

    // Dashed border to indicate empty slot
    g.setColour(color.withAlpha(0.6f));

    auto dashLength = stroke * 3.0f;
    auto gapLength = stroke * 2.0f;
    auto totalDash = dashLength + gapLength;

    // Top edge
    for (float x = slotRect.getX(); x < slotRect.getRight(); x += totalDash)
    {
        auto endX = juce::jmin(x + dashLength, slotRect.getRight());
        g.drawLine(x, slotRect.getY(), endX, slotRect.getY(), stroke);
    }

    // Bottom edge
    for (float x = slotRect.getX(); x < slotRect.getRight(); x += totalDash)
    {
        auto endX = juce::jmin(x + dashLength, slotRect.getRight());
        g.drawLine(x, slotRect.getBottom(), endX, slotRect.getBottom(), stroke);
    }

    // Left edge
    for (float y = slotRect.getY(); y < slotRect.getBottom(); y += totalDash)
    {
        auto endY = juce::jmin(y + dashLength, slotRect.getBottom());
        g.drawLine(slotRect.getX(), y, slotRect.getX(), endY, stroke);
    }

    // Right edge
    for (float y = slotRect.getY(); y < slotRect.getBottom(); y += totalDash)
    {
        auto endY = juce::jmin(y + dashLength, slotRect.getBottom());
        g.drawLine(slotRect.getRight(), y, slotRect.getRight(), endY, stroke);
    }

    // Plus symbol in center (add effect indicator)
    auto center = slotRect.getCentre();
    auto plusSize = juce::jmin(slotRect.getWidth(), slotRect.getHeight()) * 0.2f;

    g.setColour(color.withAlpha(0.5f));
    g.drawLine(center.x - plusSize, center.y, center.x + plusSize, center.y, stroke * 1.2f);
    g.drawLine(center.x, center.y - plusSize, center.x, center.y + plusSize, stroke * 1.2f);

    // "EMPTY" label
    g.setColour(color.withAlpha(0.4f));
    g.setFont(juce::Font(slotRect.getHeight() * 0.15f, juce::Font::bold));
    g.drawText("EMPTY", juce::Rectangle<float>(center.x - plusSize * 2.0f, center.y + plusSize * 1.5f,
                                             plusSize * 4.0f, slotRect.getHeight() * 0.2f),
               juce::Justification::centred);
}

// Specialized Effects
// ============================================================================

void FancyIconPack::drawTransientShaper(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Transient shaping - attack and sustain modification
    auto centerY = iconBounds.getCentreY();
    auto baseY = iconBounds.getBottom() - iconBounds.getHeight() * 0.1f;

    // Original transient (sharp attack, normal decay)
    juce::Path originalTransient;
    originalTransient.startNewSubPath(iconBounds.getX(), baseY);
    originalTransient.lineTo(iconBounds.getX() + iconBounds.getWidth() * 0.15f, iconBounds.getY() + iconBounds.getHeight() * 0.2f); // Sharp attack
    originalTransient.quadraticTo(iconBounds.getX() + iconBounds.getWidth() * 0.3f, iconBounds.getY() + iconBounds.getHeight() * 0.4f,
                                 iconBounds.getX() + iconBounds.getWidth() * 0.5f, baseY); // Natural decay

    g.setColour(color.withAlpha(0.4f));
    g.strokePath(originalTransient, createStroke(stroke * 0.8f));

    // Shaped transient (enhanced attack, modified sustain)
    juce::Path shapedTransient;
    shapedTransient.startNewSubPath(iconBounds.getX(), baseY);
    shapedTransient.lineTo(iconBounds.getX() + iconBounds.getWidth() * 0.12f, iconBounds.getY() + iconBounds.getHeight() * 0.15f); // Enhanced attack
    shapedTransient.quadraticTo(iconBounds.getX() + iconBounds.getWidth() * 0.25f, iconBounds.getY() + iconBounds.getHeight() * 0.3f,
                               iconBounds.getX() + iconBounds.getWidth() * 0.6f, iconBounds.getY() + iconBounds.getHeight() * 0.7f); // Modified sustain
    shapedTransient.lineTo(iconBounds.getRight(), baseY);

    g.setColour(color);
    g.strokePath(shapedTransient, createStroke(stroke * 1.2f));

    // Attack enhancement indicator
    juce::Path attackArrow;
    auto attackX = iconBounds.getX() + iconBounds.getWidth() * 0.2f;
    auto attackY = iconBounds.getY() + iconBounds.getHeight() * 0.35f;

    attackArrow.startNewSubPath(attackX, attackY);
    attackArrow.lineTo(attackX - stroke * 1.5f, attackY - stroke * 2.0f);
    attackArrow.lineTo(attackX + stroke * 1.5f, attackY - stroke * 2.0f);
    attackArrow.closeSubPath();

    g.setColour(color.withAlpha(0.8f));
    g.fillPath(attackArrow);

    // Sustain modification indicator
    auto sustainX = iconBounds.getX() + iconBounds.getWidth() * 0.7f;
    auto sustainY = iconBounds.getY() + iconBounds.getHeight() * 0.6f;
    auto sustainWidth = iconBounds.getWidth() * 0.08f;
    auto sustainHeight = iconBounds.getHeight() * 0.1f;

    // Only draw if dimensions are reasonable
    if (sustainWidth > stroke * 0.5f && sustainHeight > stroke * 0.5f)
    {
        juce::Path sustainCurve;
        sustainCurve.addCentredArc(sustainX, sustainY, sustainWidth, sustainHeight,
                                  0.0f, -juce::MathConstants<float>::pi * 0.5f, juce::MathConstants<float>::pi * 0.5f, true);

        g.setColour(color.withAlpha(0.7f));
        g.strokePath(sustainCurve, createStroke(stroke * 0.8f));
    }

    // Control labels
    g.setColour(color.withAlpha(0.6f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.08f, juce::Font::bold));

    g.drawText("ATK", juce::Rectangle<float>(attackX - iconBounds.getWidth() * 0.05f, attackY + stroke * 2.0f,
                                           iconBounds.getWidth() * 0.1f, iconBounds.getHeight() * 0.1f),
               juce::Justification::centred);

    g.drawText("SUS", juce::Rectangle<float>(sustainX - iconBounds.getWidth() * 0.05f, sustainY + iconBounds.getHeight() * 0.12f,
                                           iconBounds.getWidth() * 0.1f, iconBounds.getHeight() * 0.1f),
               juce::Justification::centred);
}

void FancyIconPack::drawPitchShifter(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Pitch shifting arrows showing frequency change
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();

    // Input signal (horizontal line)
    g.setColour(color.withAlpha(0.7f));
    g.drawLine(iconBounds.getX(), centerY, centerX - iconBounds.getWidth() * 0.15f, centerY, stroke);

    // Output signal (shifted)
    g.drawLine(centerX + iconBounds.getWidth() * 0.15f, centerY, iconBounds.getRight(), centerY, stroke);

    // Pitch shift processor (diamond shape)
    juce::Path processor;
    auto diamondSize = iconBounds.getWidth() * 0.12f;

    processor.startNewSubPath(centerX, centerY - diamondSize);
    processor.lineTo(centerX + diamondSize, centerY);
    processor.lineTo(centerX, centerY + diamondSize);
    processor.lineTo(centerX - diamondSize, centerY);
    processor.closeSubPath();

    g.setColour(color.withAlpha(0.3f));
    g.fillPath(processor);
    g.setColour(color);
    g.strokePath(processor, createStroke(stroke));

    // Pitch up arrow
    juce::Path pitchUpArrow;
    auto upArrowX = centerX;
    auto upArrowY = centerY - iconBounds.getHeight() * 0.25f;
    auto arrowSize = iconBounds.getWidth() * 0.06f;

    pitchUpArrow.startNewSubPath(upArrowX, upArrowY - arrowSize);
    pitchUpArrow.lineTo(upArrowX - arrowSize * 0.8f, upArrowY + arrowSize * 0.5f);
    pitchUpArrow.lineTo(upArrowX + arrowSize * 0.8f, upArrowY + arrowSize * 0.5f);
    pitchUpArrow.closeSubPath();

    g.setColour(color.withAlpha(0.8f));
    g.fillPath(pitchUpArrow);

    // Pitch down arrow
    juce::Path pitchDownArrow;
    auto downArrowX = centerX;
    auto downArrowY = centerY + iconBounds.getHeight() * 0.25f;

    pitchDownArrow.startNewSubPath(downArrowX, downArrowY + arrowSize);
    pitchDownArrow.lineTo(downArrowX - arrowSize * 0.8f, downArrowY - arrowSize * 0.5f);
    pitchDownArrow.lineTo(downArrowX + arrowSize * 0.8f, downArrowY - arrowSize * 0.5f);
    pitchDownArrow.closeSubPath();

    g.setColour(color.withAlpha(0.6f));
    g.fillPath(pitchDownArrow);

    // Frequency visualization (sine waves at different frequencies)
    juce::Path inputFreq;
    auto inputY = centerY - iconBounds.getHeight() * 0.15f;
    auto inputAmplitude = iconBounds.getHeight() * 0.08f;

    inputFreq.startNewSubPath(iconBounds.getX(), inputY);

    for (int i = 1; i <= 12; ++i)
    {
        auto x = iconBounds.getX() + (i / 12.0f) * iconBounds.getWidth() * 0.3f;
        auto phase = (i / 12.0f) * juce::MathConstants<float>::twoPi * 1.0f; // Normal frequency
        auto y = inputY + std::sin(phase) * inputAmplitude;
        inputFreq.lineTo(x, y);
    }

    g.setColour(color.withAlpha(0.5f));
    g.strokePath(inputFreq, createStroke(stroke * 0.7f));

    // Output frequency (higher pitch)
    juce::Path outputFreq;
    auto outputY = centerY + iconBounds.getHeight() * 0.15f;

    outputFreq.startNewSubPath(centerX + iconBounds.getWidth() * 0.2f, outputY);

    for (int i = 1; i <= 12; ++i)
    {
        auto x = centerX + iconBounds.getWidth() * 0.2f + (i / 12.0f) * iconBounds.getWidth() * 0.3f;
        auto phase = (i / 12.0f) * juce::MathConstants<float>::twoPi * 1.5f; // Higher frequency
        auto y = outputY + std::sin(phase) * inputAmplitude;
        outputFreq.lineTo(x, y);
    }

    g.setColour(color.withAlpha(0.7f));
    g.strokePath(outputFreq, createStroke(stroke * 0.7f));

    // Semitone indicators
    g.setColour(color.withAlpha(0.6f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.08f, juce::Font::bold));

    g.drawText("+", juce::Rectangle<float>(upArrowX - arrowSize, upArrowY - arrowSize * 2.0f,
                                        arrowSize * 2.0f, arrowSize),
               juce::Justification::centred);

    g.drawText("-", juce::Rectangle<float>(downArrowX - arrowSize, downArrowY + arrowSize,
                                         arrowSize * 2.0f, arrowSize),
               juce::Justification::centred);
}

void FancyIconPack::drawLofi(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Lo-fi degradation effects - pixelated waveform and artifacts
    auto centerY = iconBounds.getCentreY();

    // Clean signal (top, faded)
    juce::Path cleanSignal;
    auto cleanY = centerY - iconBounds.getHeight() * 0.2f;
    auto amplitude = iconBounds.getHeight() * 0.12f;

    cleanSignal.startNewSubPath(iconBounds.getX(), cleanY);

    for (int i = 1; i <= 20; ++i)
    {
        auto x = iconBounds.getX() + (i / 20.0f) * iconBounds.getWidth();
        auto phase = (i / 20.0f) * juce::MathConstants<float>::twoPi * 1.5f;
        auto y = cleanY + std::sin(phase) * amplitude;
        cleanSignal.lineTo(x, y);
    }

    g.setColour(color.withAlpha(0.3f));
    g.strokePath(cleanSignal, createStroke(stroke * 0.7f));

    // Lo-fi degraded signal (pixelated/stepped)
    juce::Path lofiSignal;
    auto lofiY = centerY + iconBounds.getHeight() * 0.2f;
    auto pixelSteps = 8; // Low resolution

    lofiSignal.startNewSubPath(iconBounds.getX(), lofiY);

    for (int i = 0; i <= pixelSteps; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(pixelSteps)) * iconBounds.getWidth();
        auto phase = (i / static_cast<float>(pixelSteps)) * juce::MathConstants<float>::twoPi * 1.5f;

        // Quantize the signal (bit reduction)
        auto smoothValue = std::sin(phase);
        auto quantizedValue = std::round(smoothValue * 3.0f) / 3.0f; // 2-bit quantization
        auto y = lofiY + quantizedValue * amplitude;

        if (i == 0)
        {
            lofiSignal.startNewSubPath(x, y);
        }
        else
        {
            // Create pixelated steps
            auto prevX = iconBounds.getX() + ((i-1) / static_cast<float>(pixelSteps)) * iconBounds.getWidth();
            auto prevPhase = ((i-1) / static_cast<float>(pixelSteps)) * juce::MathConstants<float>::twoPi * 1.5f;
            auto prevQuantized = std::round(std::sin(prevPhase) * 3.0f) / 3.0f;
            auto prevY = lofiY + prevQuantized * amplitude;

            lofiSignal.lineTo(prevX, prevY); // Hold
            lofiSignal.lineTo(x, prevY);     // Step horizontally
            lofiSignal.lineTo(x, y);         // Step vertically
        }
    }

    g.setColour(color);
    g.strokePath(lofiSignal, createStroke(stroke * 1.2f, juce::PathStrokeType::mitered, juce::PathStrokeType::butt));

    // Degradation indicators (noise/artifacts)
    juce::Random random(456);
    g.setColour(color.withAlpha(0.4f));

    for (int i = 0; i < 8; ++i)
    {
        auto x = iconBounds.getX() + random.nextFloat() * iconBounds.getWidth();
        auto y = iconBounds.getY() + random.nextFloat() * iconBounds.getHeight();
        auto artifactSize = stroke * 0.8f;

        // Small noise artifacts
        g.fillRect(x - artifactSize * 0.5f, y - artifactSize * 0.5f, artifactSize, artifactSize);
    }

    // Sample rate reduction indicator
    g.setColour(color.withAlpha(0.6f));
    auto sampleY = iconBounds.getBottom() - iconBounds.getHeight() * 0.15f;

    for (int i = 0; i < pixelSteps; ++i)
    {
        auto x = iconBounds.getX() + (i + 0.5f) * (iconBounds.getWidth() / pixelSteps);
        auto tickHeight = iconBounds.getHeight() * 0.05f;

        g.drawLine(x, sampleY - tickHeight, x, sampleY + tickHeight, stroke * 0.7f);
    }

    // "LO-FI" label
    g.setColour(color.withAlpha(0.8f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.1f, juce::Font::bold));
    g.drawText("LO-FI", juce::Rectangle<float>(iconBounds.getX(), iconBounds.getY(),
                                             iconBounds.getWidth(), iconBounds.getHeight() * 0.12f),
               juce::Justification::centred);
}

void FancyIconPack::drawStereoImager(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Stereo field visualization
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto fieldRadius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.35f;

    // Outer stereo field circle
    g.setColour(color.withAlpha(0.4f));
    g.drawEllipse(centerX - fieldRadius, centerY - fieldRadius, fieldRadius * 2, fieldRadius * 2, stroke);

    // Center axis (mono)
    g.setColour(color.withAlpha(0.6f));
    g.drawLine(centerX, centerY - fieldRadius, centerX, centerY + fieldRadius, stroke * 0.8f);

    // Left/Right indicators
    g.setColour(color);
    auto indicatorRadius = fieldRadius * 0.1f;

    // Left field indicator
    auto leftX = centerX - fieldRadius * 0.7f;
    g.fillEllipse(leftX - indicatorRadius, centerY - indicatorRadius, indicatorRadius * 2, indicatorRadius * 2);

    // Right field indicator
    auto rightX = centerX + fieldRadius * 0.7f;
    g.fillEllipse(rightX - indicatorRadius, centerY - indicatorRadius, indicatorRadius * 2, indicatorRadius * 2);

    // Stereo spread visualization (curved lines)
    juce::Path leftSpread;
    leftSpread.startNewSubPath(centerX, centerY);
    leftSpread.quadraticTo(centerX - fieldRadius * 0.3f, centerY - fieldRadius * 0.5f, leftX, centerY);

    juce::Path rightSpread;
    rightSpread.startNewSubPath(centerX, centerY);
    rightSpread.quadraticTo(centerX + fieldRadius * 0.3f, centerY - fieldRadius * 0.5f, rightX, centerY);

    g.setColour(color.withAlpha(0.7f));
    g.strokePath(leftSpread, createStroke(stroke * 0.8f));
    g.strokePath(rightSpread, createStroke(stroke * 0.8f));

    // L/R labels
    g.setFont(juce::Font(iconBounds.getHeight() * 0.15f, juce::Font::bold));
    g.drawText("L", juce::Rectangle<float>(leftX - indicatorRadius * 2, centerY + fieldRadius * 0.3f,
                                         indicatorRadius * 4, iconBounds.getHeight() * 0.15f), juce::Justification::centred);
    g.drawText("R", juce::Rectangle<float>(rightX - indicatorRadius * 2, centerY + fieldRadius * 0.3f,
                                         indicatorRadius * 4, iconBounds.getHeight() * 0.15f), juce::Justification::centred);

    // Center point
    g.setColour(color.brighter(0.3f));
    auto centerRadius = stroke * 1.2f;
    g.fillEllipse(centerX - centerRadius, centerY - centerRadius, centerRadius * 2, centerRadius * 2);
}

void FancyIconPack::drawUtility(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Utility tool symbol - wrench/gear combination
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto toolSize = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.35f;

    // Gear/cog
    auto gearRadius = toolSize * 0.5f;
    auto gearCenter = juce::Point<float>(centerX + toolSize * 0.2f, centerY - toolSize * 0.2f);

    // Outer gear teeth
    juce::Path gear;
    auto toothCount = 8;
    auto innerRadius = gearRadius * 0.7f;
    auto outerRadius = gearRadius;

    for (int i = 0; i < toothCount * 2; ++i)
    {
        auto angle = (i / static_cast<float>(toothCount * 2)) * juce::MathConstants<float>::twoPi;
        auto radius = (i % 2 == 0) ? outerRadius : innerRadius;
        auto x = gearCenter.x + std::cos(angle) * radius;
        auto y = gearCenter.y + std::sin(angle) * radius;

        if (i == 0)
            gear.startNewSubPath(x, y);
        else
            gear.lineTo(x, y);
    }
    gear.closeSubPath();

    g.setColour(color);
    g.strokePath(gear, createStroke(stroke));

    // Gear center hole
    auto centerHoleRadius = gearRadius * 0.25f;
    g.drawEllipse(gearCenter.x - centerHoleRadius, gearCenter.y - centerHoleRadius,
                 centerHoleRadius * 2, centerHoleRadius * 2, stroke);

    // Wrench
    auto wrenchCenter = juce::Point<float>(centerX - toolSize * 0.3f, centerY + toolSize * 0.3f);
    auto wrenchLength = toolSize * 0.8f;
    auto wrenchWidth = toolSize * 0.15f;

    // Wrench handle
    auto handleAngle = -0.8f; // radians
    auto handleStart = wrenchCenter;
    auto handleEnd = handleStart + juce::Point<float>(std::cos(handleAngle) * wrenchLength,
                                                     std::sin(handleAngle) * wrenchLength);

    g.drawLine(handleStart.x, handleStart.y, handleEnd.x, handleEnd.y, stroke * 1.5f);

    // Wrench head (simplified)
    auto headSize = wrenchWidth * 2;
    juce::Path wrenchHead;
    wrenchHead.addRoundedRectangle(handleEnd.x - headSize * 0.5f, handleEnd.y - headSize * 0.3f,
                                  headSize, headSize * 0.6f, 2.0f);

    g.strokePath(wrenchHead, createStroke(stroke));

    // Small screws/bolts around the icon
    auto screwRadius = stroke * 0.8f;
    auto screwPositions = {
        juce::Point<float>(iconBounds.getX() + iconBounds.getWidth() * 0.15f, iconBounds.getY() + iconBounds.getHeight() * 0.15f),
        juce::Point<float>(iconBounds.getRight() - iconBounds.getWidth() * 0.15f, iconBounds.getY() + iconBounds.getHeight() * 0.15f),
        juce::Point<float>(iconBounds.getRight() - iconBounds.getWidth() * 0.15f, iconBounds.getBottom() - iconBounds.getHeight() * 0.15f)
    };

    g.setColour(color.withAlpha(0.6f));
    for (auto& pos : screwPositions)
    {
        g.fillEllipse(pos.x - screwRadius, pos.y - screwRadius, screwRadius * 2, screwRadius * 2);
        // Cross pattern on screw
        g.setColour(color.withAlpha(0.8f));
        g.drawLine(pos.x - screwRadius * 0.5f, pos.y, pos.x + screwRadius * 0.5f, pos.y, stroke * 0.4f);
        g.drawLine(pos.x, pos.y - screwRadius * 0.5f, pos.x, pos.y + screwRadius * 0.5f, stroke * 0.4f);
        g.setColour(color.withAlpha(0.6f));
    }
}

void FancyIconPack::drawAnalyzer(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Spectrum analyzer display
    auto analyzerArea = iconBounds.reduced(iconBounds.getWidth() * 0.1f, iconBounds.getHeight() * 0.15f);

    // Background frame
    g.setColour(color.withAlpha(0.3f));
    g.drawRoundedRectangle(analyzerArea, 2.0f, stroke * 0.8f);

    // Frequency bins
    auto binCount = 12;
    auto binWidth = analyzerArea.getWidth() / static_cast<float>(binCount);
    auto maxHeight = analyzerArea.getHeight();

    g.setColour(color);

    // Create frequency response pattern (typical low-mid peak)
    juce::Array<float> binHeights;
    for (int i = 0; i < binCount; ++i)
    {
        auto freq = i / static_cast<float>(binCount - 1);

        // Create realistic spectrum shape
        float height;
        if (freq < 0.1f) height = 0.3f + freq * 2.0f; // Low freq rolloff
        else if (freq < 0.3f) height = 0.8f + (freq - 0.1f) * 1.0f; // Low-mid boost
        else if (freq < 0.6f) height = 1.0f - (freq - 0.3f) * 0.5f; // Mid slope
        else height = 0.85f - (freq - 0.6f) * 1.5f; // High freq rolloff

        // Add some variation
        height += (std::sin(freq * 20.0f) * 0.1f);
        height = juce::jlimit(0.1f, 1.0f, height);

        binHeights.add(height);
    }

    // Draw spectrum bins
    for (int i = 0; i < binCount; ++i)
    {
        auto x = analyzerArea.getX() + i * binWidth;
        auto binHeight = binHeights[i] * maxHeight;
        auto y = analyzerArea.getBottom() - binHeight;

        // Gradient effect for height
        auto alpha = 0.4f + binHeights[i] * 0.6f;
        g.setColour(color.withAlpha(alpha));

        // Bar with slight spacing
        auto barWidth = binWidth * 0.8f;
        g.fillRoundedRectangle(x + binWidth * 0.1f, y, barWidth, binHeight, 1.0f);
    }

    // Frequency grid lines
    g.setColour(color.withAlpha(0.2f));
    for (int i = 1; i < 4; ++i)
    {
        auto gridY = analyzerArea.getY() + (i / 4.0f) * analyzerArea.getHeight();
        g.drawLine(analyzerArea.getX(), gridY, analyzerArea.getRight(), gridY, stroke * 0.4f);
    }

    // Peak indicator
    g.setColour(color.brighter(0.3f));
    auto peakBin = 3; // Peak around bin 3
    auto peakX = analyzerArea.getX() + peakBin * binWidth + binWidth * 0.5f;
    auto peakY = analyzerArea.getBottom() - binHeights[peakBin] * maxHeight - stroke * 2;
    auto peakRadius = stroke;
    g.fillEllipse(peakX - peakRadius, peakY - peakRadius, peakRadius * 2, peakRadius * 2);

    // "ANALYZER" label
    g.setColour(color.withAlpha(0.8f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.1f, juce::Font::bold));
    auto labelArea = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.15f,
                                          iconBounds.getWidth(), iconBounds.getHeight() * 0.12f);
    g.drawText("ANALYZER", labelArea, juce::Justification::centred);
}

void FancyIconPack::drawTuner(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Tuning fork with pitch meter
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();

    // Tuning fork
    auto forkHeight = iconBounds.getHeight() * 0.6f;
    auto forkWidth = iconBounds.getWidth() * 0.3f;
    auto forkTop = centerY - forkHeight * 0.3f;
    auto forkBottom = centerY + forkHeight * 0.3f;

    // Fork prongs
    auto prongSpacing = forkWidth * 0.6f;
    auto leftProngX = centerX - prongSpacing * 0.5f;
    auto rightProngX = centerX + prongSpacing * 0.5f;

    g.setColour(color);

    // Left prong
    g.drawLine(leftProngX, forkTop, leftProngX, forkTop + forkHeight * 0.4f, stroke * 1.5f);
    // Right prong
    g.drawLine(rightProngX, forkTop, rightProngX, forkTop + forkHeight * 0.4f, stroke * 1.5f);

    // Fork base (U-shape)
    juce::Path forkBase;
    auto baseY = forkTop + forkHeight * 0.4f;
    forkBase.startNewSubPath(leftProngX, baseY);
    forkBase.quadraticTo(centerX, baseY + forkHeight * 0.15f, rightProngX, baseY);
    g.strokePath(forkBase, createStroke(stroke * 1.5f));

    // Fork handle
    g.drawLine(centerX, baseY + forkHeight * 0.1f, centerX, forkBottom, stroke * 2.0f);

    // Pitch meter below
    auto meterY = forkBottom + iconBounds.getHeight() * 0.1f;
    auto meterWidth = iconBounds.getWidth() * 0.7f;
    auto meterHeight = iconBounds.getHeight() * 0.15f;
    auto meterX = centerX - meterWidth * 0.5f;

    // Meter background
    g.setColour(color.withAlpha(0.3f));
    g.fillRoundedRectangle(meterX, meterY, meterWidth, meterHeight, 2.0f);

    g.setColour(color.withAlpha(0.6f));
    g.drawRoundedRectangle(meterX, meterY, meterWidth, meterHeight, 2.0f, stroke * 0.8f);

    // Center line (in tune)
    g.setColour(color.withAlpha(0.5f));
    g.drawLine(centerX, meterY, centerX, meterY + meterHeight, stroke * 0.6f);

    // Tuning indicator needle (slightly sharp)
    auto needleX = centerX + meterWidth * 0.15f; // Slightly to the right (sharp)
    g.setColour(color.brighter(0.2f));
    g.drawLine(needleX, meterY + meterHeight * 0.2f, needleX, meterY + meterHeight * 0.8f, stroke * 1.2f);

    // Meter scale marks
    g.setColour(color.withAlpha(0.6f));
    for (int i = -2; i <= 2; ++i)
    {
        auto markX = centerX + i * (meterWidth * 0.2f);
        auto markHeight = (i == 0) ? meterHeight * 0.6f : meterHeight * 0.3f;
        g.drawLine(markX, meterY + (meterHeight - markHeight) * 0.5f,
                  markX, meterY + (meterHeight + markHeight) * 0.5f, stroke * 0.6f);
    }

    // Vibration lines from fork
    g.setColour(color.withAlpha(0.4f));
    for (int i = 0; i < 3; ++i)
    {
        auto vibeRadius = (i + 1) * iconBounds.getWidth() * 0.1f;
        g.drawEllipse(centerX - vibeRadius, forkTop - vibeRadius * 0.3f,
                     vibeRadius * 2, vibeRadius * 0.6f, stroke * 0.5f);
    }

    // Note name
    g.setColour(color);
    g.setFont(juce::Font(iconBounds.getHeight() * 0.12f, juce::Font::bold));
    auto noteArea = juce::Rectangle<float>(centerX - iconBounds.getWidth() * 0.1f, meterY + meterHeight + stroke,
                                         iconBounds.getWidth() * 0.2f, iconBounds.getHeight() * 0.12f);
    g.drawText("A", noteArea, juce::Justification::centred);
}
