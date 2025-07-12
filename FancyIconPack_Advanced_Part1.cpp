#include "FancyIconPack.h"

// ============================================================================
// ADVANCED UI / WORKFLOW FEATURES IMPLEMENTATION - PART 1
// ============================================================================

// Parameter Control
// ============================================================================

void FancyIconPack::drawGroupParameters(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Parameter grouping - multiple parameters with bracket grouping
    auto parameterCount = 4;
    auto parameterHeight = iconBounds.getHeight() * 0.15f;
    auto parameterWidth = iconBounds.getWidth() * 0.6f;
    auto spacing = iconBounds.getHeight() * 0.05f;

    auto totalHeight = parameterCount * parameterHeight + (parameterCount - 1) * spacing;
    auto startY = iconBounds.getCentreY() - totalHeight * 0.5f;
    auto parameterX = iconBounds.getX() + iconBounds.getWidth() * 0.15f;

    g.setColour(color);

    // Draw parameter boxes
    for (int i = 0; i < parameterCount; ++i)
    {
        auto y = startY + i * (parameterHeight + spacing);
        auto alpha = 1.0f - i * 0.1f; // Slight fade for depth

        g.setColour(color.withAlpha(alpha));
        g.drawRoundedRectangle(parameterX, y, parameterWidth, parameterHeight, 2.0f, stroke * 0.8f);

        // Parameter value indicator
        // auto valueWidth = parameterWidth * (0.3f + i * 0.2f); // Different values
        // g.fillRoundedRectangle(parameterX + stroke, y + stroke, valueWidth - stroke * 2, parameterHeight - stroke * 2, 1.0f);
    }

    // Grouping bracket
    auto bracketX = iconBounds.getRight() - iconBounds.getWidth() * 0.1f;
    auto bracketTop = startY - spacing;
    auto bracketBottom = startY + totalHeight + spacing;
    auto bracketWidth = iconBounds.getWidth() * 0.08f;

    g.setColour(color);

    // Right bracket shape
    juce::Path bracket;
    bracket.startNewSubPath(bracketX, bracketTop);
    bracket.lineTo(bracketX + bracketWidth, bracketTop);
    bracket.lineTo(bracketX + bracketWidth, bracketTop + spacing * 0.5f);
    bracket.startNewSubPath(bracketX + bracketWidth, bracketBottom - spacing * 0.5f);
    bracket.lineTo(bracketX + bracketWidth, bracketBottom);
    bracket.lineTo(bracketX, bracketBottom);

    // Vertical line
    bracket.startNewSubPath(bracketX + bracketWidth, bracketTop + spacing * 0.5f);
    bracket.lineTo(bracketX + bracketWidth, bracketBottom - spacing * 0.5f);

    g.strokePath(bracket, createStroke(stroke));

    // Group label
    g.setFont(juce::Font(iconBounds.getHeight() * 0.1f, juce::Font::bold));
    auto labelArea = juce::Rectangle<float>(bracketX - iconBounds.getWidth() * 0.15f, bracketTop - spacing,
                                          iconBounds.getWidth() * 0.2f, spacing);
    g.drawText("GRP", labelArea, juce::Justification::centred);
}

void FancyIconPack::drawLinkControls(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Control linking - two knobs/controls connected with chain link
    auto controlRadius = iconBounds.getWidth() * 0.15f;
    auto leftCenter = juce::Point<float>(iconBounds.getX() + controlRadius * 1.5f, iconBounds.getCentreY());
    auto rightCenter = juce::Point<float>(iconBounds.getRight() - controlRadius * 1.5f, iconBounds.getCentreY());

    g.setColour(color);

    // Left control (knob)
    g.drawEllipse(leftCenter.x - controlRadius, leftCenter.y - controlRadius,
                 controlRadius * 2, controlRadius * 2, stroke);

    // Knob pointer
    auto pointerLength = controlRadius * 0.6f;
    auto pointerAngle = -juce::MathConstants<float>::pi * 0.25f; // -45 degrees
    auto pointerEnd = leftCenter + juce::Point<float>(std::cos(pointerAngle) * pointerLength,
                                                     std::sin(pointerAngle) * pointerLength);
    g.drawLine(leftCenter.x, leftCenter.y, pointerEnd.x, pointerEnd.y, stroke * 1.2f);

    // Right control (knob)
    g.drawEllipse(rightCenter.x - controlRadius, rightCenter.y - controlRadius,
                 controlRadius * 2, controlRadius * 2, stroke);

    // Knob pointer (same angle - linked)
    auto rightPointerEnd = rightCenter + juce::Point<float>(std::cos(pointerAngle) * pointerLength,
                                                           std::sin(pointerAngle) * pointerLength);
    g.drawLine(rightCenter.x, rightCenter.y, rightPointerEnd.x, rightPointerEnd.y, stroke * 1.2f);

    // Chain link connection
    auto linkY = iconBounds.getCentreY() - iconBounds.getHeight() * 0.15f;
    auto linkSpacing = (rightCenter.x - leftCenter.x - controlRadius * 2) / 3.0f;
    auto linkWidth = linkSpacing * 0.4f;
    auto linkHeight = iconBounds.getHeight() * 0.1f;

    // Draw 2 chain links
    for (int i = 0; i < 2; ++i)
    {
        auto linkX = leftCenter.x + controlRadius + linkSpacing * (i + 0.5f);
        auto linkCenterY = linkY + (i % 2) * iconBounds.getHeight() * 0.08f; // Alternate height

        // Chain link (oval)
        g.drawEllipse(linkX - linkWidth * 0.5f, linkCenterY - linkHeight * 0.5f,
                     linkWidth, linkHeight, stroke * 0.8f);
    }

    // Connection lines to controls
    auto connectionY = iconBounds.getCentreY() - iconBounds.getHeight() * 0.05f;
    g.drawLine(leftCenter.x + controlRadius, connectionY,
              leftCenter.x + controlRadius + linkSpacing * 0.3f, linkY, stroke * 0.6f);
    g.drawLine(rightCenter.x - controlRadius - linkSpacing * 0.3f, linkY,
              rightCenter.x - controlRadius, connectionY, stroke * 0.6f);

    // Link indicator symbol
    g.setFont(juce::Font(iconBounds.getHeight() * 0.08f, juce::Font::bold));
    auto linkLabelY = iconBounds.getBottom() - iconBounds.getHeight() * 0.15f;
    g.drawText("LINK", juce::Rectangle<float>(iconBounds.getX(), linkLabelY, iconBounds.getWidth(), iconBounds.getHeight() * 0.1f),
               juce::Justification::centred);
}

void FancyIconPack::drawAssignModulator(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Modulator assignment - source connecting to destination with assignment gesture
    auto sourceArea = iconBounds.removeFromLeft(iconBounds.getWidth() * 0.3f);
    auto targetArea = iconBounds.removeFromRight(iconBounds.getWidth() / 0.7f * 0.3f);
    auto connectionArea = iconBounds; // remaining middle area

    // Modulation source (LFO-like)
    auto sourceRadius = sourceArea.getHeight() * 0.25f;
    auto sourceCenter = sourceArea.getCentre();

    g.setColour(color);
    g.drawEllipse(sourceCenter.x - sourceRadius, sourceCenter.y - sourceRadius,
                 sourceRadius * 2, sourceRadius * 2, stroke);

    // LFO wave inside source
    juce::Path lfoWave;
    auto waveRadius = sourceRadius * 0.6f;
    auto points = 8;

    lfoWave.startNewSubPath(sourceCenter.x - waveRadius, sourceCenter.y);
    for (int i = 1; i <= points; ++i)
    {
        auto angle = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 1.5f;
        auto x = sourceCenter.x - waveRadius + (i / static_cast<float>(points)) * waveRadius * 2;
        auto y = sourceCenter.y + std::sin(angle) * waveRadius * 0.4f;
        lfoWave.lineTo(x, y);
    }

    g.strokePath(lfoWave, createStroke(stroke * 0.8f));

    // Target parameter (knob)
    auto targetRadius = targetArea.getHeight() * 0.25f;
    auto targetCenter = targetArea.getCentre();

    g.drawEllipse(targetCenter.x - targetRadius, targetCenter.y - targetRadius,
                 targetRadius * 2, targetRadius * 2, stroke);

    // Parameter value indicator
    auto valueAngle = juce::MathConstants<float>::pi * 0.3f; // Some value position
    auto valueLength = targetRadius * 0.7f;
    auto valueEnd = targetCenter + juce::Point<float>(std::cos(valueAngle) * valueLength,
                                                     std::sin(valueAngle) * valueLength);
    g.drawLine(targetCenter.x, targetCenter.y, valueEnd.x, valueEnd.y, stroke * 1.2f);

    // Assignment connection with modulation indicator
    auto connectionY = iconBounds.getCentreY();
    auto startX = sourceCenter.x + sourceRadius;
    auto endX = targetCenter.x - targetRadius;

    // Main connection line
    g.drawLine(startX, connectionY, endX, connectionY, stroke);

    // Assignment cursor/crosshair in middle
    auto cursorCenter = juce::Point<float>((startX + endX) * 0.5f, connectionY);
    auto cursorSize = stroke * 3;

    // Crosshair
    g.drawLine(cursorCenter.x - cursorSize, cursorCenter.y, cursorCenter.x + cursorSize, cursorCenter.y, stroke);
    g.drawLine(cursorCenter.x, cursorCenter.y - cursorSize, cursorCenter.x, cursorCenter.y + cursorSize, stroke);

    // Center dot
    auto dotRadius = stroke * 0.8f;
    g.fillEllipse(cursorCenter.x - dotRadius, cursorCenter.y - dotRadius, dotRadius * 2, dotRadius * 2);

    // Assignment arrow
    auto arrowSize = stroke * 2;
    auto arrowX = endX - arrowSize * 2;

    juce::Path arrow;
    arrow.startNewSubPath(arrowX - arrowSize, connectionY - arrowSize * 0.6f);
    arrow.lineTo(arrowX, connectionY);
    arrow.lineTo(arrowX - arrowSize, connectionY + arrowSize * 0.6f);

    g.strokePath(arrow, createStroke(stroke, juce::PathStrokeType::mitered, juce::PathStrokeType::butt));

    // Labels
    g.setFont(juce::Font(iconBounds.getHeight() * 0.08f, juce::Font::bold));

    auto sourceLabel = juce::Rectangle<float>(sourceArea.getX(), sourceCenter.y + sourceRadius + stroke,
                                            sourceArea.getWidth(), iconBounds.getHeight() * 0.1f);
    g.drawText("MOD", sourceLabel, juce::Justification::centred);

    auto targetLabel = juce::Rectangle<float>(targetArea.getX(), targetCenter.y + targetRadius + stroke,
                                            targetArea.getWidth(), iconBounds.getHeight() * 0.1f);
    g.drawText("DEST", targetLabel, juce::Justification::centred);
}

void FancyIconPack::drawLearnMode(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Learning mode - brain/neural network or graduation cap with signal
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();

    // Brain/neural network representation
    auto networkRadius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.35f;

    // Neural nodes
    juce::Array<juce::Point<float>> nodes = {
        // Input layer
        juce::Point<float>(centerX - networkRadius, centerY - networkRadius * 0.5f),
        juce::Point<float>(centerX - networkRadius, centerY + networkRadius * 0.5f),
        // Hidden layer
        juce::Point<float>(centerX, centerY - networkRadius * 0.7f),
        juce::Point<float>(centerX, centerY),
        juce::Point<float>(centerX, centerY + networkRadius * 0.7f),
        // Output layer
        juce::Point<float>(centerX + networkRadius, centerY)
    };

    g.setColour(color.withAlpha(0.6f));

    // Neural connections
    // Input to hidden
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 2; j < 5; ++j)
        {
            g.drawLine(nodes[i].x, nodes[i].y, nodes[j].x, nodes[j].y, stroke * 0.6f);
        }
    }

    // Hidden to output
    for (int i = 2; i < 5; ++i)
    {
        g.drawLine(nodes[i].x, nodes[i].y, nodes[5].x, nodes[5].y, stroke * 0.6f);
    }

    // Draw nodes
    g.setColour(color);
    auto nodeRadius = stroke * 1.5f;

    for (int i = 0; i < nodes.size(); ++i)
    {
        auto& node = nodes[i];

        // Different colors for different layers
        if (i < 2) g.setColour(color.withAlpha(0.7f)); // Input
        else if (i < 5) g.setColour(color); // Hidden
        else g.setColour(color.brighter(0.2f)); // Output

        g.fillEllipse(node.x - nodeRadius, node.y - nodeRadius, nodeRadius * 2, nodeRadius * 2);

        // Active learning indicator on some nodes
        if (i == 2 || i == 3 || i == 5)
        {
            g.setColour(color.brighter(0.5f));
            auto pulseRadius = nodeRadius * 1.5f;
            g.drawEllipse(node.x - pulseRadius, node.y - pulseRadius, pulseRadius * 2, pulseRadius * 2, stroke * 0.5f);
        }
    }

    // Learning signal/wave
    auto signalArea = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getY(),
                                           iconBounds.getWidth(), iconBounds.getHeight() * 0.2f);

    juce::Path learningSignal;
    auto signalY = signalArea.getCentreY();
    auto signalPoints = 6;

    learningSignal.startNewSubPath(signalArea.getX(), signalY);
    for (int i = 1; i <= signalPoints; ++i)
    {
        auto x = signalArea.getX() + (i / static_cast<float>(signalPoints)) * signalArea.getWidth();
        auto phase = (i / static_cast<float>(signalPoints)) * juce::MathConstants<float>::twoPi * 2;
        auto amp = std::sin(phase) * signalArea.getHeight() * 0.3f;
        learningSignal.lineTo(x, signalY + amp);
    }

    g.setColour(color.withAlpha(0.8f));
    g.strokePath(learningSignal, createStroke(stroke * 0.8f));

    // "LEARN" label
    g.setColour(color);
    g.setFont(juce::Font(iconBounds.getHeight() * 0.12f, juce::Font::bold));
    auto labelArea = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.15f,
                                          iconBounds.getWidth(), iconBounds.getHeight() * 0.12f);
    g.drawText("LEARN", labelArea, juce::Justification::centred);

    // Learning progress indicator
    auto progressArea = juce::Rectangle<float>(iconBounds.getX() + iconBounds.getWidth() * 0.1f,
                                             iconBounds.getBottom() - iconBounds.getHeight() * 0.05f,
                                             iconBounds.getWidth() * 0.8f, stroke);

    g.setColour(color.withAlpha(0.3f));
    g.fillRoundedRectangle(progressArea, stroke * 0.5f);

    g.setColour(color.brighter(0.3f));
    auto progressWidth = progressArea.getWidth() * 0.6f; // 60% learned
    g.fillRoundedRectangle(progressArea.getX(), progressArea.getY(), progressWidth, progressArea.getHeight(), stroke * 0.5f);
}

void FancyIconPack::drawVisualModulation(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Visual modulation indicators - control with visual feedback rings
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto controlRadius = juce::jmax(iconBounds.getWidth() * 0.2f, stroke * 2.0f); // Ensure minimum size

    // Main control (knob)
    g.setColour(color);
    g.fillEllipse(centerX - controlRadius, centerY - controlRadius, controlRadius * 2, controlRadius * 2);

    // Control value indicator
    auto valueAngle = juce::MathConstants<float>::pi * 0.25f; // Current value position
    auto valueLength = controlRadius * 0.7f;
    auto valueEnd = juce::Point<float>(centerX + std::cos(valueAngle) * valueLength,
                                      centerY + std::sin(valueAngle) * valueLength);

    g.setColour(color.contrasting());
    g.drawLine(centerX, centerY, valueEnd.x, valueEnd.y, stroke * 1.2f);

    // Visual modulation rings with different intensities
    auto ringCount = 3;
    auto baseRadius = controlRadius * 1.4f;

    // Ensure we have reasonable sizes before proceeding
    if (baseRadius > stroke && controlRadius > stroke * 0.5f)
    {
        for (int i = 0; i < ringCount; ++i)
        {
            auto ringRadius = baseRadius + i * controlRadius * 0.3f;
            auto alpha = juce::jmax(0.2f, 0.8f - i * 0.2f); // Ensure minimum alpha
            auto ringStroke = juce::jmax(stroke * 0.5f, stroke * (1.2f - i * 0.2f)); // Ensure minimum stroke

            // Modulation ring with varying intensity
            g.setColour(color.withAlpha(alpha));

            // Ring segments showing modulation activity
            auto segmentCount = 8;
            for (int seg = 0; seg < segmentCount; ++seg)
            {
                auto startAngle = (seg / static_cast<float>(segmentCount)) * juce::MathConstants<float>::twoPi;
                auto endAngle = ((seg + 0.7f) / static_cast<float>(segmentCount)) * juce::MathConstants<float>::twoPi;

                // Modulation activity - some segments more active
                auto activity = (seg % 3 == 0) ? 1.0f : (seg % 2 == 0) ? 0.6f : 0.3f;

                if (activity > 0.5f || i == 0)
                {
                    juce::Path ringSegment;
                    ringSegment.addCentredArc(centerX, centerY, ringRadius, ringRadius, 0.0f, startAngle, endAngle, true);

                    g.setColour(color.withAlpha(alpha * activity));
                    g.strokePath(ringSegment, createStroke(ringStroke));
                }
            }
        }

        // Modulation source indicators (small satellites)
        juce::Array<float> sourceAngles = {-juce::MathConstants<float>::pi * 0.3f,
                                          juce::MathConstants<float>::pi * 0.1f,
                                          juce::MathConstants<float>::pi * 0.7f};

        auto sourceRadius = juce::jmax(stroke, stroke * 2.0f); // Ensure minimum size
        auto sourceDistance = baseRadius + controlRadius * 0.8f;

        for (auto angle : sourceAngles)
        {
            auto sourceX = centerX + std::cos(angle) * sourceDistance;
            auto sourceY = centerY + std::sin(angle) * sourceDistance;

            // Only draw if coordinates are reasonable
            if (std::isfinite(sourceX) && std::isfinite(sourceY))
            {
                g.setColour(color.brighter(0.3f));
                g.fillEllipse(sourceX - sourceRadius, sourceY - sourceRadius, sourceRadius * 2, sourceRadius * 2);

                // Connection line to main control
                g.setColour(color.withAlpha(0.5f));
                auto connectionEndX = centerX + std::cos(angle) * baseRadius;
                auto connectionEndY = centerY + std::sin(angle) * baseRadius;

                // Ensure connection coordinates are finite
                if (std::isfinite(connectionEndX) && std::isfinite(connectionEndY))
                {
                    g.drawLine(sourceX, sourceY, connectionEndX, connectionEndY, stroke * 0.6f);
                }
            }
        }
    }

    // Visual feedback indicators (corner elements)
    g.setColour(color.withAlpha(0.6f));

    // Top-left indicator
    auto indicatorSize = juce::jmax(stroke * 2.0f, stroke * 3.0f); // Ensure reasonable size
    g.fillEllipse(iconBounds.getX(), iconBounds.getY(), indicatorSize, indicatorSize);

    // Top-right indicator
    g.fillEllipse(iconBounds.getRight() - indicatorSize, iconBounds.getY(), indicatorSize, indicatorSize);

    // Bottom-right indicator (brighter - more active)
    g.setColour(color.brighter(0.4f));
    g.fillEllipse(iconBounds.getRight() - indicatorSize, iconBounds.getBottom() - indicatorSize, indicatorSize, indicatorSize);

    // "VIS" label
    g.setColour(color);
    g.setFont(juce::Font(iconBounds.getHeight() * 0.1f, juce::Font::bold));
    auto labelArea = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.12f,
                                          iconBounds.getWidth(), iconBounds.getHeight() * 0.1f);
    g.drawText("VIS", labelArea, juce::Justification::centred);
}

void FancyIconPack::drawAnimatedKnob(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Animated knob with motion blur and trail effects
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto knobRadius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.25f;

    // Main knob body
    g.setColour(color);
    g.fillEllipse(centerX - knobRadius, centerY - knobRadius, knobRadius * 2, knobRadius * 2);

    // Animation trail - multiple pointer positions showing motion
    auto pointerLength = knobRadius * 0.7f;
    auto currentAngle = juce::MathConstants<float>::pi * 0.3f; // Current position
    auto trailPositions = 5;

    for (int i = 0; i < trailPositions; ++i)
    {
        auto trailAngle = currentAngle - (i * 0.15f); // Trail behind current position
        auto alpha = 1.0f - (i * 0.15f); // Fading trail
        auto trailLength = pointerLength * (1.0f - i * 0.1f); // Shortening trail

        auto trailEnd = juce::Point<float>(centerX + std::cos(trailAngle) * trailLength,
                                         centerY + std::sin(trailAngle) * trailLength);

        g.setColour(color.contrasting().withAlpha(alpha));
        auto trailStroke = stroke * (1.5f - i * 0.2f);
        g.drawLine(centerX, centerY, trailEnd.x, trailEnd.y, trailStroke);

        // Trail dots
        if (i > 0)
        {
            auto dotRadius = stroke * (1.0f - i * 0.15f);
            g.fillEllipse(trailEnd.x - dotRadius, trailEnd.y - dotRadius, dotRadius * 2, dotRadius * 2);
        }
    }

    // Motion blur rings
    auto blurRingCount = 3;
    for (int i = 0; i < blurRingCount; ++i)
    {
        auto blurRadius = knobRadius * (1.2f + i * 0.15f);
        auto blurAlpha = 0.3f - i * 0.08f;

        g.setColour(color.withAlpha(blurAlpha));
        g.drawEllipse(centerX - blurRadius, centerY - blurRadius, blurRadius * 2, blurRadius * 2, stroke * 0.5f);
    }

    // Speed/direction indicators
    auto speedIndicatorRadius = knobRadius * 1.8f;
    auto speedDots = 6;

    g.setColour(color.withAlpha(0.6f));
    for (int i = 0; i < speedDots; ++i)
    {
        auto dotAngle = (i / static_cast<float>(speedDots)) * juce::MathConstants<float>::twoPi;
        auto dotX = centerX + std::cos(dotAngle) * speedIndicatorRadius;
        auto dotY = centerY + std::sin(dotAngle) * speedIndicatorRadius;

        // Dots brighter in direction of motion
        auto angleDiff = std::abs(dotAngle - currentAngle);
        if (angleDiff > juce::MathConstants<float>::pi) angleDiff = juce::MathConstants<float>::twoPi - angleDiff;
        auto brightness = 1.0f - (angleDiff / juce::MathConstants<float>::pi);

        g.setColour(color.withAlpha(0.3f + brightness * 0.5f));
        auto dotSize = stroke * (0.8f + brightness * 0.7f);
        g.fillEllipse(dotX - dotSize * 0.5f, dotY - dotSize * 0.5f, dotSize, dotSize);
    }

    // Animation frame indicators (corner)
    g.setColour(color.withAlpha(0.8f));
    auto frameSize = stroke * 2;
    auto frameSpacing = stroke * 3;

    for (int i = 0; i < 3; ++i)
    {
        auto frameX = iconBounds.getRight() - frameSpacing - i * frameSpacing;
        auto frameY = iconBounds.getY() + stroke;
        auto frameAlpha = 1.0f - i * 0.3f; // Decreasing alpha for frame sequence

        g.setColour(color.withAlpha(frameAlpha));
        g.fillRoundedRectangle(frameX, frameY, frameSize, frameSize, 1.0f);
    }

    // "ANIM" label
    g.setColour(color);
    g.setFont(juce::Font(iconBounds.getHeight() * 0.1f, juce::Font::bold));
    auto labelArea = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.12f,
                                          iconBounds.getWidth(), iconBounds.getHeight() * 0.1f);
    g.drawText("ANIM", labelArea, juce::Justification::centred);

    // Direction arrow
    auto arrowSize = stroke * 2;
    auto arrowAngle = currentAngle + juce::MathConstants<float>::pi * 0.5f; // Perpendicular to pointer
    auto arrowCenter = juce::Point<float>(centerX + std::cos(currentAngle) * speedIndicatorRadius * 0.7f,
                                        centerY + std::sin(currentAngle) * speedIndicatorRadius * 0.7f);

    juce::Path arrow;
    arrow.startNewSubPath(arrowCenter.x + std::cos(arrowAngle) * arrowSize,
                         arrowCenter.y + std::sin(arrowAngle) * arrowSize);
    arrow.lineTo(arrowCenter.x + std::cos(arrowAngle + juce::MathConstants<float>::pi * 0.7f) * arrowSize,
                arrowCenter.y + std::sin(arrowAngle + juce::MathConstants<float>::pi * 0.7f) * arrowSize);
    arrow.lineTo(arrowCenter.x + std::cos(arrowAngle - juce::MathConstants<float>::pi * 0.7f) * arrowSize,
                arrowCenter.y + std::sin(arrowAngle - juce::MathConstants<float>::pi * 0.7f) * arrowSize);
    arrow.closeSubPath();

    g.setColour(color.brighter(0.3f));
    g.fillPath(arrow);
}

// Display Components
// ============================================================================

void FancyIconPack::drawSpectrumDisplay(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Spectrum analyzer with frequency bars
    auto barCount = 8;
    auto barWidth = iconBounds.getWidth() / (barCount * 1.5f);
    auto spacing = barWidth * 0.5f;
    auto maxBarHeight = iconBounds.getHeight() * 0.8f;

    g.setColour(color);

    // Frequency bars with varying heights
    juce::Array<float> barHeights = {0.3f, 0.5f, 0.8f, 0.6f, 0.9f, 0.7f, 0.4f, 0.2f};

    for (int i = 0; i < barCount; ++i)
    {
        auto barX = iconBounds.getX() + i * (barWidth + spacing);
        auto barHeight = maxBarHeight * barHeights[i];
        auto barY = iconBounds.getBottom() - barHeight;

        // Main bar
        g.fillRoundedRectangle(barX, barY, barWidth, barHeight, stroke * 0.5f);

        // Peak indicator on top
        auto peakHeight = stroke * 0.8f;
        auto peakY = barY - peakHeight - stroke;
        g.setColour(color.brighter(0.3f));
        g.fillRoundedRectangle(barX, peakY, barWidth, peakHeight, stroke * 0.2f);
        g.setColour(color);
    }

    // Frequency grid lines
    g.setColour(color.withAlpha(0.3f));
    auto gridLineCount = 3;
    for (int i = 1; i <= gridLineCount; ++i)
    {
        auto y = iconBounds.getY() + (iconBounds.getHeight() / (gridLineCount + 1)) * i;
        g.drawLine(iconBounds.getX(), y, iconBounds.getRight(), y, stroke * 0.5f);
    }
}

void FancyIconPack::drawWaveformDisplay(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Waveform display with audio wave
    juce::Path waveform;
    auto centerY = iconBounds.getCentreY();
    auto waveWidth = iconBounds.getWidth();
    auto amplitude = iconBounds.getHeight() * 0.3f;

    auto samples = 32;
    auto sampleWidth = waveWidth / static_cast<float>(samples);

    g.setColour(color);

    // Generate sine wave with some variation
    waveform.startNewSubPath(iconBounds.getX(), centerY);

    for (int i = 0; i <= samples; ++i)
    {
        auto x = iconBounds.getX() + i * sampleWidth;
        auto phase = (i / static_cast<float>(samples)) * juce::MathConstants<float>::twoPi * 2.5f;

        // Complex waveform with harmonics
        auto y = centerY + std::sin(phase) * amplitude * 0.8f +
                 std::sin(phase * 2) * amplitude * 0.3f +
                 std::sin(phase * 3) * amplitude * 0.1f;

        if (i == 0)
            waveform.startNewSubPath(x, y);
        else
            waveform.lineTo(x, y);
    }

    g.strokePath(waveform, createStroke(stroke * 1.2f));

    // Center line
    g.setColour(color.withAlpha(0.3f));
    g.drawLine(iconBounds.getX(), centerY, iconBounds.getRight(), centerY, stroke * 0.5f);

    // Time markers
    auto markerCount = 4;
    for (int i = 1; i < markerCount; ++i)
    {
        auto x = iconBounds.getX() + (iconBounds.getWidth() / markerCount) * i;
        g.drawLine(x, iconBounds.getY(), x, iconBounds.getBottom(), stroke * 0.3f);
    }
}

void FancyIconPack::drawEnvelopeDisplay(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // ADSR envelope curve
    juce::Path envelope;
    auto startX = iconBounds.getX();
    auto endX = iconBounds.getRight();
    auto topY = iconBounds.getY() + iconBounds.getHeight() * 0.2f;
    auto bottomY = iconBounds.getBottom();
    auto sustainY = iconBounds.getY() + iconBounds.getHeight() * 0.5f;

    // Envelope phases
    auto attackTime = iconBounds.getWidth() * 0.2f;
    auto decayTime = iconBounds.getWidth() * 0.2f;
    auto sustainTime = iconBounds.getWidth() * 0.4f;
    auto releaseTime = iconBounds.getWidth() * 0.2f;

    g.setColour(color);

    // Attack phase
    envelope.startNewSubPath(startX, bottomY);
    envelope.lineTo(startX + attackTime, topY);

    // Decay phase
    envelope.lineTo(startX + attackTime + decayTime, sustainY);

    // Sustain phase
    envelope.lineTo(startX + attackTime + decayTime + sustainTime, sustainY);

    // Release phase
    envelope.lineTo(endX, bottomY);

    g.strokePath(envelope, createStroke(stroke * 1.2f));

    // Phase labels with dots
    juce::Array<juce::Point<float>> phasePoints = {
        juce::Point<float>(startX, bottomY),
        juce::Point<float>(startX + attackTime, topY),
        juce::Point<float>(startX + attackTime + decayTime, sustainY),
        juce::Point<float>(startX + attackTime + decayTime + sustainTime, sustainY),
        juce::Point<float>(endX, bottomY)
    };

    auto dotRadius = stroke * 0.8f;
    g.setColour(color.brighter(0.2f));
    for (auto& point : phasePoints)
    {
        g.fillEllipse(point.x - dotRadius, point.y - dotRadius, dotRadius * 2, dotRadius * 2);
    }

    // Grid lines
    g.setColour(color.withAlpha(0.2f));
    auto gridLines = 3;
    for (int i = 1; i <= gridLines; ++i)
    {
        auto y = iconBounds.getY() + (iconBounds.getHeight() / (gridLines + 1)) * i;
        g.drawLine(iconBounds.getX(), y, iconBounds.getRight(), y, stroke * 0.3f);
    }
}

// UI Layout (Part 1)
// ============================================================================

void FancyIconPack::drawGridSnapping(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Grid with snapping indicators
    g.setColour(color.withAlpha(0.4f));

    // Grid lines
    auto gridSpacing = iconBounds.getWidth() / 4.0f;

    // Vertical grid lines
    for (int i = 1; i < 4; ++i)
    {
        auto x = iconBounds.getX() + i * gridSpacing;
        g.drawLine(x, iconBounds.getY(), x, iconBounds.getBottom(), stroke * 0.5f);
    }

    // Horizontal grid lines
    for (int i = 1; i < 4; ++i)
    {
        auto y = iconBounds.getY() + i * gridSpacing;
        g.drawLine(iconBounds.getX(), y, iconBounds.getRight(), y, stroke * 0.5f);
    }

    // Grid intersection points (snap points)
    g.setColour(color);
    auto snapRadius = stroke * 0.6f;

    for (int x = 0; x <= 4; ++x)
    {
        for (int y = 0; y <= 4; ++y)
        {
            auto snapX = iconBounds.getX() + x * gridSpacing;
            auto snapY = iconBounds.getY() + y * gridSpacing;
            g.fillEllipse(snapX - snapRadius, snapY - snapRadius, snapRadius * 2, snapRadius * 2);
        }
    }

    // Moving object being snapped
    auto objectX = iconBounds.getX() + gridSpacing * 1.8f; // Slightly off-grid
    auto objectY = iconBounds.getY() + gridSpacing * 2.3f;
    auto snapTargetX = iconBounds.getX() + gridSpacing * 2; // Grid position
    auto snapTargetY = iconBounds.getY() + gridSpacing * 2;

    // Object
    g.setColour(color.brighter(0.3f));
    auto objectSize = gridSpacing * 0.3f;
    g.fillRoundedRectangle(objectX - objectSize * 0.5f, objectY - objectSize * 0.5f,
                          objectSize, objectSize, stroke);

    // Snap target highlight
    g.setColour(color.brighter(0.5f));
    auto targetRadius = snapRadius * 2;
    g.drawEllipse(snapTargetX - targetRadius, snapTargetY - targetRadius,
                  targetRadius * 2, targetRadius * 2, stroke);

    // Snap guide lines
    g.setColour(color.withAlpha(0.6f));
    g.drawLine(objectX, objectY, snapTargetX, snapTargetY, stroke * 0.8f);
}

void FancyIconPack::drawResizablePanel(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Window/panel with resize handles
    auto panelBounds = iconBounds.reduced(stroke * 2);

    g.setColour(color);

    // Main panel outline
    g.drawRoundedRectangle(panelBounds, stroke, stroke);

    // Title bar
    auto titleBarHeight = iconBounds.getHeight() * 0.15f;
    auto titleBar = panelBounds.removeFromTop(titleBarHeight);
    g.fillRoundedRectangle(titleBar, stroke);

    // Resize handles in corners
    auto handleSize = stroke * 3;
    juce::Array<juce::Point<float>> handlePositions = {
        juce::Point<float>(panelBounds.getRight() - handleSize, panelBounds.getBottom() - handleSize), // Bottom-right
        juce::Point<float>(panelBounds.getX(), panelBounds.getBottom() - handleSize), // Bottom-left
        juce::Point<float>(panelBounds.getRight() - handleSize, panelBounds.getY()), // Top-right
    };

    g.setColour(color.brighter(0.2f));
    for (auto& pos : handlePositions)
    {
        // Corner handle with grip lines
        g.fillRect(pos.x, pos.y, handleSize, handleSize);

        // Grip lines
        g.setColour(color.darker(0.3f));
        for (int i = 0; i < 3; ++i)
        {
            auto lineOffset = stroke * (i + 1);
            g.drawLine(pos.x + lineOffset, pos.y + handleSize - stroke * 0.5f,
                      pos.x + handleSize - stroke * 0.5f, pos.y + lineOffset, stroke * 0.5f);
        }
        g.setColour(color.brighter(0.2f));
    }

    // Edge resize handles
    g.setColour(color.withAlpha(0.6f));
    auto edgeHandleSize = stroke * 1.5f;

    // Right edge handle
    auto rightEdgeY = panelBounds.getCentreY() - edgeHandleSize;
    g.fillRect(panelBounds.getRight() - stroke * 0.5f, rightEdgeY, stroke, edgeHandleSize * 2);

    // Bottom edge handle
    auto bottomEdgeX = panelBounds.getCentreX() - edgeHandleSize;
    g.fillRect(bottomEdgeX, panelBounds.getBottom() - stroke * 0.5f, edgeHandleSize * 2, stroke);
}

void FancyIconPack::drawFloatingPanel(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Floating window with shadow effect
    auto shadowOffset = stroke * 1.5f;
    auto mainPanel = iconBounds.reduced(shadowOffset);

    // Shadow
    g.setColour(color.withAlpha(0.2f));
    auto shadowPanel = mainPanel.translated(shadowOffset, shadowOffset);
    g.fillRoundedRectangle(shadowPanel, stroke * 2);

    // Main floating panel
    g.setColour(color);
    g.fillRoundedRectangle(mainPanel, stroke * 2);
    g.drawRoundedRectangle(mainPanel, stroke * 2, stroke);

    // Title bar with close button
    auto titleBarHeight = mainPanel.getHeight() * 0.2f;
    auto titleBar = mainPanel.removeFromTop(titleBarHeight);

    g.setColour(color.darker(0.2f));
    g.fillRoundedRectangle(titleBar, stroke * 2);

    // Close button
    auto closeButtonSize = titleBarHeight * 0.6f;
    auto closeButton = juce::Rectangle<float>(titleBar.getRight() - closeButtonSize - stroke * 2,
                                            titleBar.getCentreY() - closeButtonSize * 0.5f,
                                            closeButtonSize, closeButtonSize);

    g.setColour(color.brighter(0.3f));
    g.fillEllipse(closeButton);
    g.setColour(color.darker(0.5f));
    auto crossSize = closeButtonSize * 0.3f;
    auto crossCentre = closeButton.getCentre();
    g.drawLine(crossCentre.x - crossSize, crossCentre.y - crossSize,
              crossCentre.x + crossSize, crossCentre.y + crossSize, stroke * 0.8f);
    g.drawLine(crossCentre.x + crossSize, crossCentre.y - crossSize,
              crossCentre.x - crossSize, crossCentre.y + crossSize, stroke * 0.8f);

    // Panel content placeholder
    auto contentArea = mainPanel.reduced(stroke * 2);
    g.setColour(color.withAlpha(0.3f));

    // Simulate some content with lines
    auto lineSpacing = contentArea.getHeight() / 4.0f;
    for (int i = 0; i < 3; ++i)
    {
        auto y = contentArea.getY() + lineSpacing * (i + 1);
        auto lineWidth = contentArea.getWidth() * (0.8f - i * 0.1f);
        g.drawLine(contentArea.getX(), y, contentArea.getX() + lineWidth, y, stroke * 0.6f);
    }

    // Floating indicator (small arrows or similar)
    g.setColour(color.brighter(0.4f));
    auto indicatorSize = stroke * 2;
    auto indicatorX = iconBounds.getX() + stroke;
    auto indicatorY = iconBounds.getY() + stroke;

    // Small up-right arrow indicating "floating"
    juce::Path floatArrow;
    floatArrow.startNewSubPath(indicatorX, indicatorY + indicatorSize);
    floatArrow.lineTo(indicatorX, indicatorY);
    floatArrow.lineTo(indicatorX + indicatorSize, indicatorY);
    floatArrow.lineTo(indicatorX + indicatorSize * 0.7f, indicatorY + indicatorSize * 0.3f);
    floatArrow.lineTo(indicatorX + indicatorSize * 0.3f, indicatorY + indicatorSize * 0.7f);
    floatArrow.closeSubPath();

    g.fillPath(floatArrow);
}

void FancyIconPack::drawOverlay(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Multiple overlapping layers to represent overlay concept
    auto layerCount = 3;
    auto layerOffset = stroke * 2;

    // Base layer (background)
    auto baseLayer = iconBounds;
    g.setColour(color.withAlpha(0.3f));
    g.fillRoundedRectangle(baseLayer, stroke);
    g.setColour(color.withAlpha(0.6f));
    g.drawRoundedRectangle(baseLayer, stroke, stroke * 0.5f);

    // Middle layer
    auto middleLayer = baseLayer.reduced(layerOffset).translated(-layerOffset * 0.5f, -layerOffset * 0.5f);
    g.setColour(color.withAlpha(0.5f));
    g.fillRoundedRectangle(middleLayer, stroke);
    g.setColour(color.withAlpha(0.8f));
    g.drawRoundedRectangle(middleLayer, stroke, stroke * 0.7f);

    // Top layer (overlay)
    auto topLayer = middleLayer.reduced(layerOffset).translated(-layerOffset * 0.5f, -layerOffset * 0.5f);
    g.setColour(color);
    g.fillRoundedRectangle(topLayer, stroke);
    g.drawRoundedRectangle(topLayer, stroke, stroke);

    // Layer indicators (small dots or numbers)
    g.setColour(color.brighter(0.3f));
    auto dotRadius = stroke * 0.6f;

    // Dots in corners to show layering
    juce::Array<juce::Point<float>> layerIndicators = {
        juce::Point<float>(baseLayer.getRight() - stroke * 3, baseLayer.getY() + stroke * 2),
        juce::Point<float>(middleLayer.getRight() - stroke * 2, middleLayer.getY() + stroke * 1.5f),
        juce::Point<float>(topLayer.getRight() - stroke, topLayer.getY() + stroke)
    };

    for (int i = 0; i < layerIndicators.size(); ++i)
    {
        auto& pos = layerIndicators[i];
        auto brightness = 0.3f + (i * 0.3f);
        g.setColour(color.withBrightness(brightness));
        g.fillEllipse(pos.x - dotRadius, pos.y - dotRadius, dotRadius * 2, dotRadius * 2);
    }

    // Optional: transparency/blend effect indicator
    g.setColour(color.withAlpha(0.7f));
    auto blendIndicatorSize = stroke * 1.5f;
    auto blendX = topLayer.getCentreX() - blendIndicatorSize;
    auto blendY = topLayer.getCentreY() - blendIndicatorSize;

    // Draw a small "blend" symbol (overlapping circles)
    g.drawEllipse(blendX, blendY, blendIndicatorSize * 2, blendIndicatorSize * 2, stroke * 0.5f);
    g.drawEllipse(blendX + blendIndicatorSize * 0.5f, blendY + blendIndicatorSize * 0.5f,
                  blendIndicatorSize * 2, blendIndicatorSize * 2, stroke * 0.5f);
}

void FancyIconPack::drawTooltip(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Tooltip bubble with pointer
    auto bubbleHeight = iconBounds.getHeight() * 0.6f;
    auto bubbleBounds = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getY(),
                                             iconBounds.getWidth(), bubbleHeight);

    // Pointer tail
    auto tailWidth = iconBounds.getWidth() * 0.15f;
    auto tailHeight = iconBounds.getHeight() - bubbleHeight;
    auto tailStartX = iconBounds.getCentreX() - tailWidth * 0.5f;
    auto tailStartY = bubbleBounds.getBottom();

    g.setColour(color);

    // Main tooltip bubble
    g.fillRoundedRectangle(bubbleBounds, stroke * 2);
    g.drawRoundedRectangle(bubbleBounds, stroke * 2, stroke);

    // Tooltip pointer/tail
    juce::Path pointer;
    pointer.startNewSubPath(tailStartX, tailStartY);
    pointer.lineTo(tailStartX + tailWidth, tailStartY);
    pointer.lineTo(iconBounds.getCentreX(), iconBounds.getBottom());
    pointer.closeSubPath();

    g.fillPath(pointer);
    g.strokePath(pointer, createStroke(stroke));

    // Tooltip content (text lines simulation)
    auto contentArea = bubbleBounds.reduced(stroke * 2);
    g.setColour(color.withAlpha(0.7f));

    auto lineHeight = contentArea.getHeight() / 3.0f;
    auto lineY1 = contentArea.getY() + lineHeight * 0.3f;
    auto lineY2 = contentArea.getY() + lineHeight * 1.0f;
    auto lineY3 = contentArea.getY() + lineHeight * 1.7f;

    // First line (longer)
    g.drawLine(contentArea.getX(), lineY1,
              contentArea.getRight() - contentArea.getWidth() * 0.1f, lineY1, stroke * 0.6f);

    // Second line (medium)
    g.drawLine(contentArea.getX(), lineY2,
              contentArea.getRight() - contentArea.getWidth() * 0.3f, lineY2, stroke * 0.6f);

    // Third line (shorter)
    g.drawLine(contentArea.getX(), lineY3,
              contentArea.getRight() - contentArea.getWidth() * 0.5f, lineY3, stroke * 0.6f);

    // Help/info indicator (question mark or 'i')
    g.setColour(color.brighter(0.3f));
    auto infoRadius = stroke * 1.5f;
    auto infoX = bubbleBounds.getX() + stroke * 2;
    auto infoY = bubbleBounds.getY() + stroke * 2;

    g.drawEllipse(infoX, infoY, infoRadius * 2, infoRadius * 2, stroke * 0.8f);

    // Info symbol (i)
    auto symbolX = infoX + infoRadius;
    auto symbolY = infoY + infoRadius;

    // Dot on top
    auto dotRadius = stroke * 0.3f;
    g.fillEllipse(symbolX - dotRadius, symbolY - infoRadius * 0.4f, dotRadius * 2, dotRadius * 2);

    // Vertical line
    g.drawLine(symbolX, symbolY - infoRadius * 0.1f, symbolX, symbolY + infoRadius * 0.4f, stroke * 0.6f);
}
