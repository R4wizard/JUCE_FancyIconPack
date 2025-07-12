#include "FancyIconPack.h"

// ============================================================================
// MIDI AND MODULATION ICONS IMPLEMENTATION - PART 2
// ============================================================================

// Modulation Matrix
// ============================================================================

void FancyIconPack::drawModMatrix(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Modulation matrix grid
    auto gridSize = 4; // 4x4 matrix
    auto cellWidth = iconBounds.getWidth() / gridSize;
    auto cellHeight = iconBounds.getHeight() / gridSize;

    // Draw grid lines
    g.setColour(color.withAlpha(0.4f));

    // Vertical lines
    for (int i = 0; i <= gridSize; ++i)
    {
        auto x = iconBounds.getX() + i * cellWidth;
        g.drawLine(x, iconBounds.getY(), x, iconBounds.getBottom(), stroke * 0.5f);
    }

    // Horizontal lines
    for (int i = 0; i <= gridSize; ++i)
    {
        auto y = iconBounds.getY() + i * cellHeight;
        g.drawLine(iconBounds.getX(), y, iconBounds.getRight(), y, stroke * 0.5f);
    }

    // Active modulation connections (filled circles at intersections)
    struct ModConnection { int source, dest; float amount; };
    ModConnection connections[] = {
        {0, 1, 0.8f}, {1, 2, 0.6f}, {2, 0, 0.4f}, {3, 3, 1.0f}
    };

    for (const auto& conn : connections)
    {
        auto x = iconBounds.getX() + (conn.dest + 0.5f) * cellWidth;
        auto y = iconBounds.getY() + (conn.source + 0.5f) * cellHeight;
        auto radius = cellWidth * 0.15f * conn.amount;

        g.setColour(color.withAlpha(0.3f + conn.amount * 0.5f));
        g.fillEllipse(x - radius, y - radius, radius * 2.0f, radius * 2.0f);

        g.setColour(color.withAlpha(0.8f));
        g.drawEllipse(x - radius, y - radius, radius * 2.0f, radius * 2.0f, stroke * 0.7f);
    }

    // Source labels (left side)
    g.setColour(color.withAlpha(0.7f));
    g.setFont(juce::Font(cellHeight * 0.3f));
    juce::String sources[] = {"LFO", "ENV", "VEL", "KEY"};

    for (int i = 0; i < gridSize; ++i)
    {
        auto y = iconBounds.getY() + (i + 0.5f) * cellHeight;
        g.drawText(sources[i],
                  juce::Rectangle<float>(iconBounds.getX() - cellWidth * 0.4f, y - cellHeight * 0.2f,
                                       cellWidth * 0.35f, cellHeight * 0.4f),
                  juce::Justification::centredRight);
    }

    // Destination labels (top)
    juce::String destinations[] = {"FREQ", "AMP", "FLT", "PAN"};

    for (int i = 0; i < gridSize; ++i)
    {
        auto x = iconBounds.getX() + (i + 0.5f) * cellWidth;
        g.drawText(destinations[i],
                  juce::Rectangle<float>(x - cellWidth * 0.2f, iconBounds.getY() - cellHeight * 0.3f,
                                       cellWidth * 0.4f, cellHeight * 0.25f),
                  juce::Justification::centred);
    }
}

void FancyIconPack::drawModSource(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Modulation source symbol - generator with output signal
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto sourceRadius = iconBounds.getWidth() * 0.25f;

    // Source generator (circle)
    g.setColour(color.withAlpha(0.3f));
    g.fillEllipse(centerX - sourceRadius, centerY - sourceRadius, sourceRadius * 2.0f, sourceRadius * 2.0f);
    g.setColour(color);
    g.drawEllipse(centerX - sourceRadius, centerY - sourceRadius, sourceRadius * 2.0f, sourceRadius * 2.0f, stroke);

    // Source type indicator (sine wave inside)
    juce::Path sourceWave;
    auto waveAmplitude = sourceRadius * 0.4f;
    auto wavePoints = 8;

    sourceWave.startNewSubPath(centerX - sourceRadius * 0.6f, centerY);

    for (int i = 1; i <= wavePoints; ++i)
    {
        auto x = centerX - sourceRadius * 0.6f + (i / static_cast<float>(wavePoints)) * sourceRadius * 1.2f;
        auto phase = (i / static_cast<float>(wavePoints)) * juce::MathConstants<float>::twoPi;
        auto y = centerY + std::sin(phase) * waveAmplitude;
        sourceWave.lineTo(x, y);
    }

    g.setColour(color.withAlpha(0.8f));
    g.strokePath(sourceWave, createStroke(stroke * 0.8f));

    // Output signal path
    auto outputStartX = centerX + sourceRadius;
    auto outputEndX = iconBounds.getRight() - stroke;

    g.setColour(color);
    g.drawLine(outputStartX, centerY, outputEndX, centerY, stroke);

    // Output connector
    auto connectorRadius = stroke * 1.5f;
    g.fillEllipse(outputEndX - connectorRadius, centerY - connectorRadius,
                  connectorRadius * 2.0f, connectorRadius * 2.0f);

    // Signal strength indicator (variable amplitude)
    juce::Path outputSignal;
    auto signalY = centerY + iconBounds.getHeight() * 0.2f;
    auto signalAmplitude = iconBounds.getHeight() * 0.1f;

    outputSignal.startNewSubPath(outputStartX, signalY);

    for (int i = 1; i <= 6; ++i)
    {
        auto x = outputStartX + (i / 6.0f) * (outputEndX - outputStartX);
        auto phase = (i / 6.0f) * juce::MathConstants<float>::twoPi * 1.5f;
        auto y = signalY + std::sin(phase) * signalAmplitude;
        outputSignal.lineTo(x, y);
    }

    g.setColour(color.withAlpha(0.6f));
    g.strokePath(outputSignal, createStroke(stroke * 0.7f));

    // "SRC" label
    g.setColour(color.withAlpha(0.8f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.12f, juce::Font::bold));
    g.drawText("SRC", juce::Rectangle<float>(iconBounds.getX(), iconBounds.getY(),
                                           iconBounds.getWidth(), iconBounds.getHeight() * 0.15f),
               juce::Justification::centred);
}

void FancyIconPack::drawModDestination(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Modulation destination symbol - parameter being modulated
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto destRadius = iconBounds.getWidth() * 0.25f;

    // Input signal path
    auto inputStartX = iconBounds.getX() + stroke;
    auto inputEndX = centerX - destRadius;

    g.setColour(color);
    g.drawLine(inputStartX, centerY, inputEndX, centerY, stroke);

    // Input connector
    auto connectorRadius = stroke * 1.5f;
    g.fillEllipse(inputStartX - connectorRadius, centerY - connectorRadius,
                  connectorRadius * 2.0f, connectorRadius * 2.0f);

    // Destination parameter (square representing a control)
    auto paramRect = juce::Rectangle<float>(centerX - destRadius, centerY - destRadius,
                                          destRadius * 2.0f, destRadius * 2.0f);

    g.setColour(color.withAlpha(0.3f));
    g.fillRoundedRectangle(paramRect, stroke * 2.0f);
    g.setColour(color);
    g.drawRoundedRectangle(paramRect, stroke * 2.0f, stroke);

    // Parameter control (knob indicator)
    auto knobRadius = destRadius * 0.4f;
    g.setColour(color.withAlpha(0.6f));
    g.drawEllipse(centerX - knobRadius, centerY - knobRadius, knobRadius * 2.0f, knobRadius * 2.0f, stroke * 0.8f);

    // Knob pointer showing current position
    auto pointerAngle = juce::MathConstants<float>::pi * 0.3f; // 54 degrees
    auto pointerLength = knobRadius * 0.7f;
    auto pointerEndX = centerX + std::cos(pointerAngle) * pointerLength;
    auto pointerEndY = centerY + std::sin(pointerAngle) * pointerLength;

    g.setColour(color);
    g.drawLine(centerX, centerY, pointerEndX, pointerEndY, stroke * 1.2f);

    // Modulation visualization (wavy lines around parameter)
    for (int i = 0; i < 3; ++i)
    {
        auto radius = destRadius * (1.3f + i * 0.2f);
        auto alpha = juce::jmax(0.2f, 0.6f - i * 0.15f); // Ensure minimum alpha

        // Only draw if radius is reasonable
        if (radius > stroke)
        {
            juce::Path modRing;
            modRing.addCentredArc(centerX, centerY, radius, radius, 0.0f,
                                 -juce::MathConstants<float>::pi * 0.25f,
                                 juce::MathConstants<float>::pi * 0.5f, true);

            g.setColour(color.withAlpha(alpha));
            g.strokePath(modRing, createStroke(stroke * 0.7f));
        }
    }

    // Modulation amount indicator (small wave)
    juce::Path modWave;
    auto modY = centerY + destRadius * 1.8f;
    auto modAmplitude = iconBounds.getHeight() * 0.06f;

    modWave.startNewSubPath(centerX - destRadius, modY);

    for (int i = 1; i <= 8; ++i)
    {
        auto x = centerX - destRadius + (i / 8.0f) * destRadius * 2.0f;
        auto phase = (i / 8.0f) * juce::MathConstants<float>::twoPi * 2.0f;
        auto y = modY + std::sin(phase) * modAmplitude;
        modWave.lineTo(x, y);
    }

    g.setColour(color.withAlpha(0.6f));
    g.strokePath(modWave, createStroke(stroke * 0.7f));

    // "DEST" label
    g.setColour(color.withAlpha(0.8f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.12f, juce::Font::bold));
    g.drawText("DEST", juce::Rectangle<float>(iconBounds.getX(), iconBounds.getY(),
                                            iconBounds.getWidth(), iconBounds.getHeight() * 0.15f),
               juce::Justification::centred);
}

void FancyIconPack::drawModDepth(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Depth visualization - wave with increasing amplitude
    auto centerY = iconBounds.getCentreY();
    auto baseAmplitude = iconBounds.getHeight() * 0.1f;
    auto maxAmplitude = iconBounds.getHeight() * 0.4f;
    auto points = 12;

    juce::Path depthWave;
    depthWave.startNewSubPath(iconBounds.getX(), centerY);

    for (int i = 1; i <= points; ++i)
    {
        auto x = iconBounds.getX() + (i / static_cast<float>(points)) * iconBounds.getWidth();
        auto ratio = i / static_cast<float>(points);
        auto phase = ratio * juce::MathConstants<float>::twoPi * 2.0f;

        // Increasing amplitude from left to right
        auto amplitude = baseAmplitude + (maxAmplitude - baseAmplitude) * ratio;
        auto amp = std::sin(phase) * amplitude;
        depthWave.lineTo(x, centerY + amp);
    }

    g.setColour(color);
    g.strokePath(depthWave, createStroke(stroke));

    // Depth indicator arrows
    auto arrowSize = stroke * 2;

    // Small depth arrow (left)
    auto leftX = iconBounds.getX() + iconBounds.getWidth() * 0.2f;
    g.drawLine(leftX, centerY - baseAmplitude, leftX, centerY + baseAmplitude, stroke);
    g.fillEllipse(leftX - arrowSize * 0.5f, centerY - baseAmplitude - arrowSize * 0.5f, arrowSize, arrowSize);
    g.fillEllipse(leftX - arrowSize * 0.5f, centerY + baseAmplitude - arrowSize * 0.5f, arrowSize, arrowSize);

    // Large depth arrow (right)
    auto rightX = iconBounds.getX() + iconBounds.getWidth() * 0.8f;
    g.drawLine(rightX, centerY - maxAmplitude, rightX, centerY + maxAmplitude, stroke);
    g.fillEllipse(rightX - arrowSize * 0.5f, centerY - maxAmplitude - arrowSize * 0.5f, arrowSize, arrowSize);
    g.fillEllipse(rightX - arrowSize * 0.5f, centerY + maxAmplitude - arrowSize * 0.5f, arrowSize, arrowSize);
}

void FancyIconPack::drawModAmount(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Amount slider with modulation indicator
    auto sliderArea = iconBounds.reduced(iconBounds.getWidth() * 0.2f, iconBounds.getHeight() * 0.1f);
    auto sliderTrack = sliderArea.removeFromTop(sliderArea.getHeight() * 0.6f);

    // Slider track
    g.setColour(color.withAlpha(0.4f));
    auto trackThickness = stroke * 2;
    g.fillRoundedRectangle(sliderTrack.getCentreX() - trackThickness * 0.5f, sliderTrack.getY(),
                          trackThickness, sliderTrack.getHeight(), trackThickness * 0.5f);

    // Current amount position (70%)
    auto amountRatio = 0.7f;
    auto thumbY = sliderTrack.getY() + sliderTrack.getHeight() * (1.0f - amountRatio);
    auto thumbSize = iconBounds.getWidth() * 0.15f;

    g.setColour(color);
    g.fillEllipse(sliderTrack.getCentreX() - thumbSize * 0.5f, thumbY - thumbSize * 0.5f, thumbSize, thumbSize);

    // Modulation range indicator
    auto modRange = iconBounds.getHeight() * 0.15f;
    g.setColour(color.withAlpha(0.6f));
    g.fillRoundedRectangle(sliderTrack.getCentreX() - trackThickness * 1.5f, thumbY - modRange * 0.5f,
                          trackThickness * 3, modRange, trackThickness);

    // Amount scale marks
    g.setColour(color.withAlpha(0.7f));
    for (int i = 0; i <= 4; ++i)
    {
        auto markY = sliderTrack.getY() + (i / 4.0f) * sliderTrack.getHeight();
        auto markLength = (i == 0 || i == 4) ? stroke * 3 : stroke * 2;
        g.drawLine(sliderTrack.getRight() + stroke, markY, sliderTrack.getRight() + stroke + markLength, markY, stroke * 0.8f);
    }

    // "AMT" label
    g.setColour(color);
    g.setFont(juce::Font(iconBounds.getHeight() * 0.15f, juce::Font::bold));
    auto labelArea = sliderArea.removeFromBottom(sliderArea.getHeight());
    g.drawText("AMT", labelArea, juce::Justification::centred);
}

void FancyIconPack::drawModCurve(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Modulation curve with control points
    auto curveArea = iconBounds.reduced(iconBounds.getWidth() * 0.1f, iconBounds.getHeight() * 0.1f);

    // Curve path (S-curve)
    juce::Path curve;
    curve.startNewSubPath(curveArea.getX(), curveArea.getBottom());

    auto points = 10;
    for (int i = 1; i <= points; ++i)
    {
        auto ratio = i / static_cast<float>(points);
        auto x = curveArea.getX() + ratio * curveArea.getWidth();

        // S-curve using smooth step function
        auto smoothRatio = ratio * ratio * (3.0f - 2.0f * ratio);
        auto y = curveArea.getBottom() - smoothRatio * curveArea.getHeight();

        curve.lineTo(x, y);
    }

    g.setColour(color);
    g.strokePath(curve, createStroke(stroke * 1.2f));

    // Control points
    auto dotRadius = stroke * 1.5f;

    // Start point
    g.fillEllipse(curveArea.getX() - dotRadius, curveArea.getBottom() - dotRadius, dotRadius * 2, dotRadius * 2);

    // Mid control point
    auto midX = curveArea.getCentreX();
    auto midY = curveArea.getCentreY();
    g.setColour(color.brighter(0.3f));
    g.fillEllipse(midX - dotRadius, midY - dotRadius, dotRadius * 2, dotRadius * 2);

    // End point
    g.setColour(color);
    g.fillEllipse(curveArea.getRight() - dotRadius, curveArea.getY() - dotRadius, dotRadius * 2, dotRadius * 2);

    // Axis lines
    g.setColour(color.withAlpha(0.3f));
    g.drawLine(curveArea.getX(), curveArea.getBottom(), curveArea.getRight(), curveArea.getBottom(), stroke * 0.6f);
    g.drawLine(curveArea.getX(), curveArea.getBottom(), curveArea.getX(), curveArea.getY(), stroke * 0.6f);
}

void FancyIconPack::drawModShape(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Wave shape modifier - showing transformation
    auto leftArea = iconBounds.removeFromLeft(iconBounds.getWidth() * 0.4f);
    auto rightArea = iconBounds.removeFromRight(iconBounds.getWidth() / 0.6f * 0.4f);
    auto centerArea = iconBounds; // remaining center area

    // Original wave (sine)
    juce::Path originalWave;
    auto leftY = leftArea.getCentreY();
    auto leftAmplitude = leftArea.getHeight() * 0.3f;
    auto points = 8;

    originalWave.startNewSubPath(leftArea.getX(), leftY);
    for (int i = 1; i <= points; ++i)
    {
        auto x = leftArea.getX() + (i / static_cast<float>(points)) * leftArea.getWidth();
        auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 1.5f;
        auto amp = std::sin(phase) * leftAmplitude;
        originalWave.lineTo(x, leftY + amp);
    }

    // Modified wave (shaped/distorted)
    juce::Path modifiedWave;
    auto rightY = rightArea.getCentreY();
    auto rightAmplitude = rightArea.getHeight() * 0.3f;

    modifiedWave.startNewSubPath(rightArea.getX(), rightY);
    for (int i = 1; i <= points; ++i)
    {
        auto x = rightArea.getX() + (i / static_cast<float>(points)) * rightArea.getWidth();
        auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 1.5f;
        auto sineValue = std::sin(phase);

        // Apply shaping (soft clipping)
        auto shaped = std::tanh(sineValue * 2.0f) * 0.8f;
        auto amp = shaped * rightAmplitude;
        modifiedWave.lineTo(x, rightY + amp);
    }

    g.setColour(color.withAlpha(0.7f));
    g.strokePath(originalWave, createStroke(stroke));

    g.setColour(color);
    g.strokePath(modifiedWave, createStroke(stroke));

    // Transform arrow in center
    auto arrowY = centerArea.getCentreY();
    auto arrowLength = centerArea.getWidth() * 0.6f;
    auto arrowStart = centerArea.getCentreX() - arrowLength * 0.5f;
    auto arrowEnd = centerArea.getCentreX() + arrowLength * 0.5f;

    g.drawLine(arrowStart, arrowY, arrowEnd, arrowY, stroke);

    // Arrow head
    auto arrowSize = stroke * 2;
    juce::Path arrowHead;
    arrowHead.startNewSubPath(arrowEnd - arrowSize, arrowY - arrowSize);
    arrowHead.lineTo(arrowEnd, arrowY);
    arrowHead.lineTo(arrowEnd - arrowSize, arrowY + arrowSize);

    g.strokePath(arrowHead, createStroke(stroke, juce::PathStrokeType::mitered, juce::PathStrokeType::butt));

    // Shape function symbol
    g.setFont(juce::Font(centerArea.getHeight() * 0.2f, juce::Font::bold));
    g.drawText("f(x)", juce::Rectangle<float>(centerArea.getX(), arrowY + stroke * 3, centerArea.getWidth(), centerArea.getHeight() * 0.25f),
               juce::Justification::centred);
}

void FancyIconPack::drawModRouting(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Modulation routing network
    auto nodeRadius = iconBounds.getWidth() * 0.06f;
    auto dotRadius = stroke * 1.2f;

    // Source nodes (left)
    juce::Point<float> source1(iconBounds.getX() + nodeRadius * 2, iconBounds.getY() + iconBounds.getHeight() * 0.3f);
    juce::Point<float> source2(iconBounds.getX() + nodeRadius * 2, iconBounds.getY() + iconBounds.getHeight() * 0.7f);

    // Destination nodes (right)
    juce::Point<float> dest1(iconBounds.getRight() - nodeRadius * 2, iconBounds.getY() + iconBounds.getHeight() * 0.25f);
    juce::Point<float> dest2(iconBounds.getRight() - nodeRadius * 2, iconBounds.getY() + iconBounds.getHeight() * 0.75f);

    g.setColour(color);

    // Draw source nodes
    g.fillEllipse(source1.x - nodeRadius, source1.y - nodeRadius, nodeRadius * 2, nodeRadius * 2);
    g.fillEllipse(source2.x - nodeRadius, source2.y - nodeRadius, nodeRadius * 2, nodeRadius * 2);

    // Draw destination nodes
    g.drawEllipse(dest1.x - nodeRadius, dest1.y - nodeRadius, nodeRadius * 2, nodeRadius * 2, stroke);
    g.drawEllipse(dest2.x - nodeRadius, dest2.y - nodeRadius, nodeRadius * 2, nodeRadius * 2, stroke);

    // Routing connections with modulation indicators
    auto connectionAlpha = 0.8f;

    // Connection 1: source1 -> dest1
    g.setColour(color.withAlpha(connectionAlpha));
    juce::Path connection1;
    connection1.startNewSubPath(source1.x + nodeRadius, source1.y);
    auto control1 = juce::Point<float>(iconBounds.getCentreX(), source1.y - iconBounds.getHeight() * 0.1f);
    connection1.quadraticTo(control1, dest1 - juce::Point<float>(nodeRadius, 0));
    g.strokePath(connection1, createStroke(stroke));

    // Connection 2: source2 -> dest2
    juce::Path connection2;
    connection2.startNewSubPath(source2.x + nodeRadius, source2.y);
    auto control2 = juce::Point<float>(iconBounds.getCentreX(), source2.y + iconBounds.getHeight() * 0.1f);
    connection2.quadraticTo(control2, dest2 - juce::Point<float>(nodeRadius, 0));
    g.strokePath(connection2, createStroke(stroke));

    // Routing matrix indicator in center
    auto matrixSize = iconBounds.getHeight() * 0.15f;
    auto matrixCenter = iconBounds.getCentre();
    g.setColour(color.withAlpha(0.6f));
    g.fillRoundedRectangle(matrixCenter.x - matrixSize, matrixCenter.y - matrixSize * 0.5f,
                          matrixSize * 2, matrixSize, 2.0f);

    // Small routing dots
    g.setColour(color);
    g.fillEllipse(matrixCenter.x - dotRadius * 0.5f, matrixCenter.y - dotRadius * 0.5f, dotRadius, dotRadius);
    g.fillEllipse(matrixCenter.x + matrixSize * 0.5f - dotRadius * 0.5f, matrixCenter.y - dotRadius * 0.5f, dotRadius, dotRadius);
}

void FancyIconPack::drawModSignal(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Modulation signal flow with processing stages
    auto flowY = iconBounds.getCentreY();
    auto blockSize = iconBounds.getHeight() * 0.2f;

    // Input modulation wave
    auto inputArea = iconBounds.removeFromLeft(iconBounds.getWidth() * 0.25f);
    juce::Path inputWave;
    auto inputY = inputArea.getCentreY();
    auto inputAmplitude = inputArea.getHeight() * 0.15f;
    auto points = 6;

    inputWave.startNewSubPath(inputArea.getX(), inputY);
    for (int i = 1; i <= points; ++i)
    {
        auto x = inputArea.getX() + (i / static_cast<float>(points)) * inputArea.getWidth();
        auto phase = (i / static_cast<float>(points)) * juce::MathConstants<float>::twoPi * 2.0f;
        auto amp = std::sin(phase) * inputAmplitude;
        inputWave.lineTo(x, inputY + amp);
    }

    g.setColour(color.withAlpha(0.7f));
    g.strokePath(inputWave, createStroke(stroke));

    // Signal flow line
    g.setColour(color);
    g.drawLine(inputArea.getRight(), flowY, iconBounds.getRight(), flowY, stroke);

    // Processing block
    auto blockX = iconBounds.getCentreX() - blockSize * 0.5f;
    auto blockY = flowY - blockSize * 0.5f;
    g.fillRoundedRectangle(blockX, blockY, blockSize, blockSize, 2.0f);

    // Signal processing indicator (small wave inside block)
    juce::Path processWave;
    auto processArea = juce::Rectangle<float>(blockX + blockSize * 0.2f, blockY + blockSize * 0.3f,
                                            blockSize * 0.6f, blockSize * 0.4f);
    auto processY = processArea.getCentreY();
    auto processAmp = processArea.getHeight() * 0.3f;

    processWave.startNewSubPath(processArea.getX(), processY);
    for (int i = 1; i <= 4; ++i)
    {
        auto x = processArea.getX() + (i / 4.0f) * processArea.getWidth();
        auto phase = (i / 4.0f) * juce::MathConstants<float>::twoPi * 1.5f;
        auto amp = std::sin(phase) * processAmp;
        processWave.lineTo(x, processY + amp);
    }

    g.setColour(color.brighter(0.3f));
    g.strokePath(processWave, createStroke(stroke * 0.8f));

    // Output signal indicators
    g.setColour(color);
    auto outputRadius = stroke * 1.5f;
    g.fillEllipse(inputArea.getX() - outputRadius, flowY - outputRadius, outputRadius * 2, outputRadius * 2);
    g.fillEllipse(iconBounds.getRight() - outputRadius, flowY - outputRadius, outputRadius * 2, outputRadius * 2);

    // Signal direction arrows
    auto arrowSize = stroke * 1.5f;
    for (int i = 0; i < 2; ++i)
    {
        auto arrowX = inputArea.getRight() + iconBounds.getWidth() * 0.15f + i * iconBounds.getWidth() * 0.25f;
        juce::Path arrow;
        arrow.startNewSubPath(arrowX - arrowSize, flowY - arrowSize * 0.7f);
        arrow.lineTo(arrowX, flowY);
        arrow.lineTo(arrowX - arrowSize, flowY + arrowSize * 0.7f);

        g.strokePath(arrow, createStroke(stroke * 0.8f, juce::PathStrokeType::mitered, juce::PathStrokeType::butt));
    }
}

// Automation and CV
// ============================================================================

void FancyIconPack::drawAutomation(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Automation curve with control points
    auto curveArea = iconBounds.reduced(iconBounds.getWidth() * 0.1f, iconBounds.getHeight() * 0.15f);

    // Automation points
    juce::Array<juce::Point<float>> automationPoints;
    automationPoints.add(juce::Point<float>(curveArea.getX(), curveArea.getBottom() - curveArea.getHeight() * 0.2f));
    automationPoints.add(juce::Point<float>(curveArea.getX() + curveArea.getWidth() * 0.3f, curveArea.getY() + curveArea.getHeight() * 0.1f));
    automationPoints.add(juce::Point<float>(curveArea.getX() + curveArea.getWidth() * 0.7f, curveArea.getY() + curveArea.getHeight() * 0.6f));
    automationPoints.add(juce::Point<float>(curveArea.getRight(), curveArea.getBottom() - curveArea.getHeight() * 0.3f));

    // Draw automation curve
    juce::Path automationPath;
    automationPath.startNewSubPath(automationPoints[0]);

    for (int i = 1; i < automationPoints.size(); ++i)
    {
        automationPath.lineTo(automationPoints[i]);
    }

    g.setColour(color);
    g.strokePath(automationPath, createStroke(stroke * 1.2f));

    // Control points
    auto pointRadius = stroke * 1.8f;
    for (auto& point : automationPoints)
    {
        g.setColour(color.brighter(0.2f));
        g.fillEllipse(point.x - pointRadius, point.y - pointRadius, pointRadius * 2, pointRadius * 2);
        g.setColour(color);
        g.drawEllipse(point.x - pointRadius, point.y - pointRadius, pointRadius * 2, pointRadius * 2, stroke * 0.8f);
    }

    // Grid background
    g.setColour(color.withAlpha(0.2f));
    for (int i = 1; i < 4; ++i)
    {
        auto gridY = curveArea.getY() + (i / 4.0f) * curveArea.getHeight();
        g.drawLine(curveArea.getX(), gridY, curveArea.getRight(), gridY, stroke * 0.4f);
    }

    for (int i = 1; i < 4; ++i)
    {
        auto gridX = curveArea.getX() + (i / 4.0f) * curveArea.getWidth();
        g.drawLine(gridX, curveArea.getY(), gridX, curveArea.getBottom(), stroke * 0.4f);
    }

    // "AUTO" label
    g.setColour(color.withAlpha(0.8f));
    g.setFont(juce::Font(iconBounds.getHeight() * 0.12f, juce::Font::bold));
    auto labelArea = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getBottom() - iconBounds.getHeight() * 0.15f,
                                          iconBounds.getWidth(), iconBounds.getHeight() * 0.12f);
    g.drawText("AUTO", labelArea, juce::Justification::centred);
}

void FancyIconPack::drawAutomationLane(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Automation lane with track and curve
    auto laneArea = iconBounds.reduced(iconBounds.getWidth() * 0.05f, iconBounds.getHeight() * 0.1f);

    // Track background
    g.setColour(color.withAlpha(0.2f));
    g.fillRoundedRectangle(laneArea, 2.0f);

    g.setColour(color.withAlpha(0.4f));
    g.drawRoundedRectangle(laneArea, 2.0f, stroke * 0.8f);

    // Parameter name area
    auto nameArea = laneArea.removeFromLeft(laneArea.getWidth() * 0.25f);
    g.setColour(color.withAlpha(0.8f));
    g.setFont(juce::Font(nameArea.getHeight() * 0.3f, juce::Font::bold));
    g.drawText("VOL", nameArea, juce::Justification::centred);

    // Automation curve area
    auto curveArea = laneArea.reduced(laneArea.getWidth() * 0.05f, laneArea.getHeight() * 0.2f);

    // Simple automation curve
    juce::Path automationCurve;
    auto startY = curveArea.getY() + curveArea.getHeight() * 0.7f;
    auto midY = curveArea.getY() + curveArea.getHeight() * 0.2f;
    auto endY = curveArea.getY() + curveArea.getHeight() * 0.5f;

    automationCurve.startNewSubPath(curveArea.getX(), startY);
    automationCurve.lineTo(curveArea.getCentreX(), midY);
    automationCurve.lineTo(curveArea.getRight(), endY);

    g.setColour(color);
    g.strokePath(automationCurve, createStroke(stroke));

    // Automation points
    auto pointRadius = stroke * 1.2f;
    g.fillEllipse(curveArea.getX() - pointRadius, startY - pointRadius, pointRadius * 2, pointRadius * 2);
    g.fillEllipse(curveArea.getCentreX() - pointRadius, midY - pointRadius, pointRadius * 2, pointRadius * 2);
    g.fillEllipse(curveArea.getRight() - pointRadius, endY - pointRadius, pointRadius * 2, pointRadius * 2);

    // Timeline grid
    g.setColour(color.withAlpha(0.3f));
    for (int i = 1; i < 4; ++i)
    {
        auto gridX = curveArea.getX() + (i / 4.0f) * curveArea.getWidth();
        g.drawLine(gridX, curveArea.getY(), gridX, curveArea.getBottom(), stroke * 0.4f);
    }
}

void FancyIconPack::drawAutomationCurve(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Automation curve editor interface
    auto editorArea = iconBounds.reduced(iconBounds.getWidth() * 0.1f, iconBounds.getHeight() * 0.1f);

    // Editor background
    g.setColour(color.withAlpha(0.2f));
    g.fillRoundedRectangle(editorArea, 2.0f);
    g.setColour(color.withAlpha(0.4f));
    g.drawRoundedRectangle(editorArea, 2.0f, stroke * 0.6f);

    // Grid
    g.setColour(color.withAlpha(0.15f));
    for (int i = 1; i < 4; ++i)
    {
        auto gridX = editorArea.getX() + (i / 4.0f) * editorArea.getWidth();
        auto gridY = editorArea.getY() + (i / 4.0f) * editorArea.getHeight();
        g.drawLine(gridX, editorArea.getY(), gridX, editorArea.getBottom(), stroke * 0.4f);
        g.drawLine(editorArea.getX(), gridY, editorArea.getRight(), gridY, stroke * 0.4f);
    }

    // Automation curve with multiple segments
    juce::Array<juce::Point<float>> curvePoints;
    curvePoints.add(juce::Point<float>(editorArea.getX(), editorArea.getBottom() - editorArea.getHeight() * 0.3f));
    curvePoints.add(juce::Point<float>(editorArea.getX() + editorArea.getWidth() * 0.25f, editorArea.getY() + editorArea.getHeight() * 0.1f));
    curvePoints.add(juce::Point<float>(editorArea.getX() + editorArea.getWidth() * 0.5f, editorArea.getY() + editorArea.getHeight() * 0.4f));
    curvePoints.add(juce::Point<float>(editorArea.getX() + editorArea.getWidth() * 0.75f, editorArea.getY() + editorArea.getHeight() * 0.7f));
    curvePoints.add(juce::Point<float>(editorArea.getRight(), editorArea.getBottom() - editorArea.getHeight() * 0.2f));

    // Draw curve segments
    juce::Path curvePath;
    curvePath.startNewSubPath(curvePoints[0]);

    for (int i = 1; i < curvePoints.size(); ++i)
    {
        curvePath.lineTo(curvePoints[i]);
    }

    g.setColour(color);
    g.strokePath(curvePath, createStroke(stroke));

    // Control points
    auto pointRadius = stroke * 1.5f;
    for (int i = 0; i < curvePoints.size(); ++i)
    {
        auto& point = curvePoints[i];

        // Different colors for different point types
        if (i == 0 || i == curvePoints.size() - 1)
            g.setColour(color.withAlpha(0.7f)); // Endpoints
        else
            g.setColour(color.brighter(0.2f)); // Control points

        g.fillEllipse(point.x - pointRadius, point.y - pointRadius, pointRadius * 2, pointRadius * 2);

        // Selection indicator on middle point
        if (i == 2)
        {
            g.setColour(color.brighter(0.5f));
            g.drawEllipse(point.x - pointRadius * 1.5f, point.y - pointRadius * 1.5f,
                         pointRadius * 3, pointRadius * 3, stroke * 0.8f);
        }
    }

    // Time ruler at bottom
    g.setColour(color.withAlpha(0.6f));
    auto rulerY = editorArea.getBottom() + stroke;
    g.drawLine(editorArea.getX(), rulerY, editorArea.getRight(), rulerY, stroke * 0.6f);

    // Time markers
    for (int i = 0; i <= 4; ++i)
    {
        auto markerX = editorArea.getX() + (i / 4.0f) * editorArea.getWidth();
        g.drawLine(markerX, rulerY - stroke, markerX, rulerY + stroke, stroke * 0.6f);
    }
}

void FancyIconPack::drawCV(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Control Voltage signal representation
    auto waveArea = iconBounds.removeFromTop(iconBounds.getHeight() * 0.6f);

    // CV signal (stepped voltage levels)
    juce::Path cvSignal;
    auto baseY = waveArea.getBottom();
    auto steps = 6;
    auto stepWidth = waveArea.getWidth() / static_cast<float>(steps);

    // Generate stepped CV pattern
    juce::Array<float> voltageSteps = {0.2f, 0.7f, 0.4f, 0.9f, 0.3f, 0.6f};

    cvSignal.startNewSubPath(waveArea.getX(), baseY);

    for (int i = 0; i < steps; ++i)
    {
        auto x = waveArea.getX() + i * stepWidth;
        auto nextX = waveArea.getX() + (i + 1) * stepWidth;
        auto voltage = voltageSteps[i];
        auto y = baseY - voltage * waveArea.getHeight();

        // Vertical rise
        cvSignal.lineTo(x, y);
        // Horizontal hold
        cvSignal.lineTo(nextX, y);
    }

    g.setColour(color);
    g.strokePath(cvSignal, createStroke(stroke * 1.2f, juce::PathStrokeType::mitered, juce::PathStrokeType::butt));

    // Voltage level indicators
    g.setColour(color.withAlpha(0.4f));
    for (int i = 1; i <= 4; ++i)
    {
        auto levelY = baseY - (i / 5.0f) * waveArea.getHeight();
        g.drawLine(waveArea.getX(), levelY, waveArea.getX() + stepWidth * 0.3f, levelY, stroke * 0.6f);

        // Voltage labels
        g.setFont(juce::Font(waveArea.getHeight() * 0.12f));
        g.drawText(juce::String(i) + "V",
                  juce::Rectangle<float>(waveArea.getX() - stepWidth * 0.2f, levelY - waveArea.getHeight() * 0.06f,
                                       stepWidth * 0.3f, waveArea.getHeight() * 0.12f),
                  juce::Justification::centredRight);
    }

    // "CV" label
    g.setColour(color);
    g.setFont(juce::Font(iconBounds.getHeight() * 0.25f, juce::Font::bold));
    auto labelArea = iconBounds.removeFromBottom(iconBounds.getHeight());
    g.drawText("CV", labelArea, juce::Justification::centred);

    // Control voltage symbol (lightning bolt)
    auto symbolArea = labelArea.removeFromRight(labelArea.getWidth() * 0.3f);
    juce::Path lightning;
    auto centerX = symbolArea.getCentreX();
    auto centerY = symbolArea.getCentreY();
    auto size = symbolArea.getHeight() * 0.3f;

    lightning.startNewSubPath(centerX - size * 0.3f, centerY - size * 0.5f);
    lightning.lineTo(centerX + size * 0.2f, centerY - size * 0.1f);
    lightning.lineTo(centerX - size * 0.1f, centerY);
    lightning.lineTo(centerX + size * 0.3f, centerY + size * 0.5f);
    lightning.lineTo(centerX - size * 0.2f, centerY + size * 0.1f);
    lightning.lineTo(centerX + size * 0.1f, centerY);
    lightning.closeSubPath();

    g.setColour(color.withAlpha(0.7f));
    g.fillPath(lightning);
}

void FancyIconPack::drawCVIn(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // CV input jack (1/4" or 3.5mm style)
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto jackRadius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.3f;

    // Outer jack ring
    g.setColour(color);
    g.drawEllipse(centerX - jackRadius, centerY - jackRadius, jackRadius * 2, jackRadius * 2, stroke * 1.2f);

    // Inner conductor ring
    auto innerRadius = jackRadius * 0.6f;
    g.drawEllipse(centerX - innerRadius, centerY - innerRadius, innerRadius * 2, innerRadius * 2, stroke);

    // Center hole
    auto holeRadius = jackRadius * 0.25f;
    g.setColour(color.withAlpha(0.8f));
    g.fillEllipse(centerX - holeRadius, centerY - holeRadius, holeRadius * 2, holeRadius * 2);

    // Input signal arrow pointing into jack
    auto arrowSize = jackRadius * 0.4f;
    auto arrowX = centerX - jackRadius * 1.8f;

    juce::Path inputArrow;
    inputArrow.startNewSubPath(arrowX - arrowSize, centerY);
    inputArrow.lineTo(arrowX, centerY - arrowSize * 0.6f);
    inputArrow.lineTo(arrowX - arrowSize * 0.4f, centerY);
    inputArrow.lineTo(arrowX, centerY + arrowSize * 0.6f);
    inputArrow.closeSubPath();

    g.setColour(color);
    g.fillPath(inputArrow);

    // Signal flow line
    g.drawLine(arrowX, centerY, centerX - jackRadius, centerY, stroke);

    // CV signal representation (small waveform above jack)
    auto waveArea = juce::Rectangle<float>(centerX - jackRadius * 0.8f, centerY - jackRadius * 2.2f,
                                         jackRadius * 1.6f, jackRadius * 0.6f);

    juce::Path cvWave;
    auto waveY = waveArea.getCentreY();
    auto points = 6;

    cvWave.startNewSubPath(waveArea.getX(), waveY);
    for (int i = 1; i <= points; ++i)
    {
        auto x = waveArea.getX() + (i / static_cast<float>(points)) * waveArea.getWidth();
        // Stepped CV pattern
        auto step = std::floor((i / static_cast<float>(points)) * 3) / 3.0f;
        auto y = waveY - step * waveArea.getHeight() * 0.4f;
        cvWave.lineTo(x, y);
    }

    g.setColour(color.withAlpha(0.7f));
    g.strokePath(cvWave, createStroke(stroke * 0.8f, juce::PathStrokeType::mitered, juce::PathStrokeType::butt));

    // "IN" label
    g.setColour(color);
    g.setFont(juce::Font(iconBounds.getHeight() * 0.15f, juce::Font::bold));
    auto labelArea = juce::Rectangle<float>(iconBounds.getX(), centerY + jackRadius * 1.5f,
                                          iconBounds.getWidth(), iconBounds.getHeight() * 0.15f);
    g.drawText("CV IN", labelArea, juce::Justification::centred);

    // Jack mounting threads (cosmetic detail)
    g.setColour(color.withAlpha(0.4f));
    auto threadRadius = jackRadius * 1.15f;
    for (int i = 0; i < 8; ++i)
    {
        auto angle = (i / 8.0f) * juce::MathConstants<float>::twoPi;
        auto startR = threadRadius - stroke * 0.5f;
        auto endR = threadRadius + stroke * 0.5f;
        auto x1 = centerX + std::cos(angle) * startR;
        auto y1 = centerY + std::sin(angle) * startR;
        auto x2 = centerX + std::cos(angle) * endR;
        auto y2 = centerY + std::sin(angle) * endR;
        g.drawLine(x1, y1, x2, y2, stroke * 0.4f);
    }
}

void FancyIconPack::drawCVOut(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // CV output jack (1/4" or 3.5mm style)
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto jackRadius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.3f;

    // Outer jack ring
    g.setColour(color);
    g.drawEllipse(centerX - jackRadius, centerY - jackRadius, jackRadius * 2, jackRadius * 2, stroke * 1.2f);

    // Inner conductor ring
    auto innerRadius = jackRadius * 0.6f;
    g.drawEllipse(centerX - innerRadius, centerY - innerRadius, innerRadius * 2, innerRadius * 2, stroke);

    // Center hole
    auto holeRadius = jackRadius * 0.25f;
    g.setColour(color.withAlpha(0.8f));
    g.fillEllipse(centerX - holeRadius, centerY - holeRadius, holeRadius * 2, holeRadius * 2);

    // Output signal arrow pointing out from jack
    auto arrowSize = jackRadius * 0.4f;
    auto arrowX = centerX + jackRadius * 1.8f;

    juce::Path outputArrow;
    outputArrow.startNewSubPath(arrowX - arrowSize * 0.4f, centerY);
    outputArrow.lineTo(arrowX, centerY - arrowSize * 0.6f);
    outputArrow.lineTo(arrowX + arrowSize, centerY);
    outputArrow.lineTo(arrowX, centerY + arrowSize * 0.6f);
    outputArrow.closeSubPath();

    g.setColour(color);
    g.fillPath(outputArrow);

    // Signal flow line
    g.drawLine(centerX + jackRadius, centerY, arrowX - arrowSize * 0.4f, centerY, stroke);

    // CV signal representation (small waveform above jack)
    auto waveArea = juce::Rectangle<float>(centerX - jackRadius * 0.8f, centerY - jackRadius * 2.2f,
                                         jackRadius * 1.6f, jackRadius * 0.6f);

    juce::Path cvWave;
    auto waveY = waveArea.getCentreY();
    auto points = 6;

    cvWave.startNewSubPath(waveArea.getX(), waveY);
    for (int i = 1; i <= points; ++i)
    {
        auto x = waveArea.getX() + (i / static_cast<float>(points)) * waveArea.getWidth();
        // Stepped CV pattern (different from input for visual distinction)
        auto step = std::floor((i / static_cast<float>(points)) * 4) / 4.0f;
        auto y = waveY - step * waveArea.getHeight() * 0.5f;
        cvWave.lineTo(x, y);
    }

    g.setColour(color.withAlpha(0.7f));
    g.strokePath(cvWave, createStroke(stroke * 0.8f, juce::PathStrokeType::mitered, juce::PathStrokeType::butt));

    // Signal activity indicator (LED-like)
    g.setColour(color.brighter(0.4f));
    auto ledRadius = stroke * 1.5f;
    auto ledX = centerX + jackRadius * 0.7f;
    auto ledY = centerY - jackRadius * 0.7f;
    g.fillEllipse(ledX - ledRadius, ledY - ledRadius, ledRadius * 2, ledRadius * 2);

    // "OUT" label
    g.setColour(color);
    g.setFont(juce::Font(iconBounds.getHeight() * 0.15f, juce::Font::bold));
    auto labelArea = juce::Rectangle<float>(iconBounds.getX(), centerY + jackRadius * 1.5f,
                                          iconBounds.getWidth(), iconBounds.getHeight() * 0.15f);
    g.drawText("CV OUT", labelArea, juce::Justification::centred);

    // Jack mounting threads (cosmetic detail)
    g.setColour(color.withAlpha(0.4f));
    auto threadRadius = jackRadius * 1.15f;
    for (int i = 0; i < 8; ++i)
    {
        auto angle = (i / 8.0f) * juce::MathConstants<float>::twoPi;
        auto startR = threadRadius - stroke * 0.5f;
        auto endR = threadRadius + stroke * 0.5f;
        auto x1 = centerX + std::cos(angle) * startR;
        auto y1 = centerY + std::sin(angle) * startR;
        auto x2 = centerX + std::cos(angle) * endR;
        auto y2 = centerY + std::sin(angle) * endR;
        g.drawLine(x1, y1, x2, y2, stroke * 0.4f);
    }
}
