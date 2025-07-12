#include "FancyIconPack.h"

// ============================================================================
// GENERAL UI / WORKFLOW ICONS IMPLEMENTATION - PART 2
// ============================================================================

// Layout and View Controls
// ============================================================================

void FancyIconPack::drawScrollHorizontal(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Track
    auto trackBounds = iconBounds.withSizeKeepingCentre(iconBounds.getWidth() * 0.8f, stroke * 2.0f);
    g.setColour(color.withAlpha(0.4f));
    g.fillRoundedRectangle(trackBounds, stroke);

    // Thumb
    auto thumbWidth = trackBounds.getWidth() * 0.3f;
    auto thumbBounds = juce::Rectangle<float>(trackBounds.getX() + trackBounds.getWidth() * 0.35f,
                                            trackBounds.getY() - stroke, thumbWidth, stroke * 4.0f);
    g.setColour(color);
    g.fillRoundedRectangle(thumbBounds, stroke * 2.0f);
}

void FancyIconPack::drawScrollVertical(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Track
    auto trackBounds = iconBounds.withSizeKeepingCentre(stroke * 2.0f, iconBounds.getHeight() * 0.8f);
    g.setColour(color.withAlpha(0.4f));
    g.fillRoundedRectangle(trackBounds, stroke);

    // Thumb
    auto thumbHeight = trackBounds.getHeight() * 0.3f;
    auto thumbBounds = juce::Rectangle<float>(trackBounds.getX() - stroke,
                                            trackBounds.getY() + trackBounds.getHeight() * 0.35f,
                                            stroke * 4.0f, thumbHeight);
    g.setColour(color);
    g.fillRoundedRectangle(thumbBounds, stroke * 2.0f);
}

void FancyIconPack::drawGrid(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    g.setColour(color);

    // Draw 3x3 grid
    auto cellSize = iconBounds.getWidth() / 3.0f;
    for (int i = 0; i <= 3; ++i)
    {
        float x = iconBounds.getX() + i * cellSize;
        float y = iconBounds.getY() + i * cellSize;

        // Vertical lines
        g.drawLine(x, iconBounds.getY(), x, iconBounds.getBottom(), stroke);
        // Horizontal lines
        g.drawLine(iconBounds.getX(), y, iconBounds.getRight(), y, stroke);
    }
}

void FancyIconPack::drawList(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    g.setColour(color);

    // Draw 4 horizontal lines representing list items
    auto lineHeight = iconBounds.getHeight() / 5.0f;
    for (int i = 0; i < 4; ++i)
    {
        float y = iconBounds.getY() + (i + 0.5f) * lineHeight;
        g.drawLine(iconBounds.getX(), y, iconBounds.getRight(), y, stroke * 1.5f);
    }
}

void FancyIconPack::drawLock(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    auto lockBodyHeight = iconBounds.getHeight() * 0.6f;
    auto lockBodyY = iconBounds.getBottom() - lockBodyHeight;
    auto lockBody = juce::Rectangle<float>(iconBounds.getX(), lockBodyY, iconBounds.getWidth(), lockBodyHeight);

    // Lock body
    g.setColour(color);
    g.fillRoundedRectangle(lockBody, 3.0f);

    // Shackle (the curved part)
    auto shackleWidth = iconBounds.getWidth() * 0.6f;
    auto shackleHeight = iconBounds.getHeight() * 0.5f;
    auto shackleX = iconBounds.getCentreX() - shackleWidth * 0.5f;
    auto shackleY = iconBounds.getY();

    g.setColour(color);
    g.drawEllipse(shackleX, shackleY, shackleWidth, shackleHeight, stroke * 1.5f);

    // Remove bottom part of ellipse to create shackle
    g.setColour(juce::Colours::transparentBlack);
    auto eraseRect = juce::Rectangle<float>(shackleX - stroke, lockBodyY - stroke,
                                          shackleWidth + stroke * 2, lockBodyHeight + stroke * 2);
    g.fillRect(eraseRect);

    // Redraw lock body
    g.setColour(color);
    g.fillRoundedRectangle(lockBody, 3.0f);

    // Keyhole
    auto keyholeSize = iconBounds.getWidth() * 0.15f;
    auto keyholeBounds = juce::Rectangle<float>(iconBounds.getCentreX() - keyholeSize * 0.5f,
                                              lockBodyY + lockBodyHeight * 0.3f, keyholeSize, keyholeSize);
    g.setColour(juce::Colours::black);
    g.fillEllipse(keyholeBounds);
}

void FancyIconPack::drawUnlock(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    auto lockBodyHeight = iconBounds.getHeight() * 0.6f;
    auto lockBodyY = iconBounds.getBottom() - lockBodyHeight;
    auto lockBody = juce::Rectangle<float>(iconBounds.getX(), lockBodyY, iconBounds.getWidth(), lockBodyHeight);

    // Lock body
    g.setColour(color);
    g.fillRoundedRectangle(lockBody, 3.0f);

    // Open shackle (partial arc)
    auto shackleWidth = iconBounds.getWidth() * 0.6f;
    auto shackleHeight = iconBounds.getHeight() * 0.5f;
    auto shackleX = iconBounds.getCentreX() - shackleWidth * 0.5f;
    auto shackleY = iconBounds.getY();

    juce::Path shackle;
    shackle.addCentredArc(shackleX + shackleWidth * 0.5f, shackleY + shackleHeight * 0.5f,
                         shackleWidth * 0.5f, shackleHeight * 0.5f, 0.0f,
                         juce::MathConstants<float>::pi, juce::MathConstants<float>::pi * 1.7f, true);

    g.setColour(color);
    g.strokePath(shackle, juce::PathStrokeType(stroke * 1.5f, juce::PathStrokeType::curved));

    // Keyhole
    auto keyholeSize = iconBounds.getWidth() * 0.15f;
    auto keyholeBounds = juce::Rectangle<float>(iconBounds.getCentreX() - keyholeSize * 0.5f,
                                              lockBodyY + lockBodyHeight * 0.3f, keyholeSize, keyholeSize);
    g.setColour(juce::Colours::black);
    g.fillEllipse(keyholeBounds);
}

void FancyIconPack::drawBypass(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    g.setColour(color);

    // Draw circle with diagonal line through it
    g.drawEllipse(iconBounds, stroke * 1.5f);

    // Diagonal line from top-left to bottom-right
    auto lineStart = iconBounds.getTopLeft() + juce::Point<float>(iconBounds.getWidth() * 0.2f, iconBounds.getHeight() * 0.2f);
    auto lineEnd = iconBounds.getBottomRight() - juce::Point<float>(iconBounds.getWidth() * 0.2f, iconBounds.getHeight() * 0.2f);

    g.drawLine(lineStart.x, lineStart.y, lineEnd.x, lineEnd.y, stroke * 2.0f);
}

void FancyIconPack::drawPower(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    g.setColour(color);

    // Power button circle (incomplete)
    auto radius = iconBounds.getWidth() * 0.5f;
    auto centre = iconBounds.getCentre();

    juce::Path powerArc;
    powerArc.addCentredArc(centre.x, centre.y, radius * 0.8f, radius * 0.8f, 0.0f,
                          juce::MathConstants<float>::pi * 0.7f,
                          juce::MathConstants<float>::pi * 2.3f, true);

    g.strokePath(powerArc, juce::PathStrokeType(stroke * 1.5f, juce::PathStrokeType::curved));

    // Power button line (vertical line at top)
    auto lineHeight = radius * 0.6f;
    g.drawLine(centre.x, centre.y - lineHeight, centre.x, centre.y + lineHeight * 0.2f, stroke * 1.5f);
}

void FancyIconPack::drawRefresh(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    g.setColour(color);

    auto centre = iconBounds.getCentre();
    auto radius = iconBounds.getWidth() * 0.4f;

    // Circular arrow
    juce::Path refreshPath;
    refreshPath.addCentredArc(centre.x, centre.y, radius, radius, 0.0f,
                             juce::MathConstants<float>::pi * 0.2f,
                             juce::MathConstants<float>::pi * 1.8f, true);

    g.strokePath(refreshPath, juce::PathStrokeType(stroke * 1.5f, juce::PathStrokeType::curved));

    // Arrow head
    auto arrowTip = centre + juce::Point<float>(radius * std::cos(juce::MathConstants<float>::pi * 1.8f),
                                               radius * std::sin(juce::MathConstants<float>::pi * 1.8f));
    auto arrowSize = stroke * 3.0f;

    juce::Path arrow;
    arrow.startNewSubPath(arrowTip);
    arrow.lineTo(arrowTip + juce::Point<float>(-arrowSize, -arrowSize * 0.5f));
    arrow.lineTo(arrowTip + juce::Point<float>(-arrowSize * 0.5f, -arrowSize));
    arrow.closeSubPath();

    g.fillPath(arrow);
}

// File Operations
// ============================================================================

void FancyIconPack::drawDownload(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    g.setColour(color);

    // Vertical line (download shaft)
    auto shaftHeight = iconBounds.getHeight() * 0.6f;
    auto shaftX = iconBounds.getCentreX();
    auto shaftTop = iconBounds.getY();
    auto shaftBottom = shaftTop + shaftHeight;

    g.drawLine(shaftX, shaftTop, shaftX, shaftBottom, stroke * 1.5f);

    // Arrow head pointing down
    auto arrowSize = iconBounds.getWidth() * 0.3f;
    juce::Path arrow;
    arrow.startNewSubPath(shaftX, shaftBottom);
    arrow.lineTo(shaftX - arrowSize * 0.5f, shaftBottom - arrowSize * 0.5f);
    arrow.lineTo(shaftX + arrowSize * 0.5f, shaftBottom - arrowSize * 0.5f);
    arrow.closeSubPath();

    g.fillPath(arrow);

    // Base line
    auto baseY = iconBounds.getBottom() - stroke;
    g.drawLine(iconBounds.getX(), baseY, iconBounds.getRight(), baseY, stroke * 1.5f);
}

void FancyIconPack::drawUpload(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    g.setColour(color);

    // Vertical line (upload shaft)
    auto shaftHeight = iconBounds.getHeight() * 0.6f;
    auto shaftX = iconBounds.getCentreX();
    auto shaftBottom = iconBounds.getBottom();
    auto shaftTop = shaftBottom - shaftHeight;

    g.drawLine(shaftX, shaftTop, shaftX, shaftBottom, stroke * 1.5f);

    // Arrow head pointing up
    auto arrowSize = iconBounds.getWidth() * 0.3f;
    juce::Path arrow;
    arrow.startNewSubPath(shaftX, shaftTop);
    arrow.lineTo(shaftX - arrowSize * 0.5f, shaftTop + arrowSize * 0.5f);
    arrow.lineTo(shaftX + arrowSize * 0.5f, shaftTop + arrowSize * 0.5f);
    arrow.closeSubPath();

    g.fillPath(arrow);

    // Base line
    auto baseY = iconBounds.getY() + stroke;
    g.drawLine(iconBounds.getX(), baseY, iconBounds.getRight(), baseY, stroke * 1.5f);
}

void FancyIconPack::drawExternalLink(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    g.setColour(color);

    // Main square
    auto squareSize = iconBounds.getWidth() * 0.7f;
    auto square = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getBottom() - squareSize, squareSize, squareSize);
    g.drawRoundedRectangle(square, 2.0f, stroke);

    // Arrow box in top right
    auto arrowBoxSize = iconBounds.getWidth() * 0.4f;
    auto arrowBox = juce::Rectangle<float>(iconBounds.getRight() - arrowBoxSize, iconBounds.getY(), arrowBoxSize, arrowBoxSize);
    g.drawRoundedRectangle(arrowBox, 1.0f, stroke);

    // Arrow pointing out
    auto arrowCentre = arrowBox.getCentre();
    auto arrowOffset = arrowBoxSize * 0.2f;
    g.drawLine(arrowCentre.x - arrowOffset, arrowCentre.y + arrowOffset,
              arrowCentre.x + arrowOffset, arrowCentre.y - arrowOffset, stroke);

    // Arrow head
    g.drawLine(arrowCentre.x + arrowOffset, arrowCentre.y - arrowOffset,
              arrowCentre.x, arrowCentre.y - arrowOffset, stroke);
    g.drawLine(arrowCentre.x + arrowOffset, arrowCentre.y - arrowOffset,
              arrowCentre.x + arrowOffset, arrowCentre.y, stroke);
}

void FancyIconPack::drawPin(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    g.setColour(color);

    // Pin head (circle)
    auto headRadius = iconBounds.getWidth() * 0.3f;
    auto headCentre = iconBounds.getTopLeft() + juce::Point<float>(iconBounds.getWidth() * 0.3f, headRadius);
    g.fillEllipse(headCentre.x - headRadius, headCentre.y - headRadius, headRadius * 2, headRadius * 2);

    // Pin body (angled line)
    auto bodyEnd = iconBounds.getBottomRight() - juce::Point<float>(iconBounds.getWidth() * 0.2f, iconBounds.getHeight() * 0.2f);
    g.drawLine(headCentre.x, headCentre.y, bodyEnd.x, bodyEnd.y, stroke * 2.0f);

    // Pin point
    auto pointSize = stroke * 2.0f;
    g.fillEllipse(bodyEnd.x - pointSize * 0.5f, bodyEnd.y - pointSize * 0.5f, pointSize, pointSize);
}

void FancyIconPack::drawDragHandle(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    g.setColour(color);

    // Draw 6 dots in 2 columns, 3 rows
    auto dotSize = stroke * 1.5f;
    auto spacing = iconBounds.getHeight() / 4.0f;

    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 2; ++col)
        {
            auto x = iconBounds.getX() + col * (iconBounds.getWidth() * 0.5f) + iconBounds.getWidth() * 0.25f;
            auto y = iconBounds.getY() + (row + 0.5f) * spacing;

            g.fillEllipse(x - dotSize * 0.5f, y - dotSize * 0.5f, dotSize, dotSize);
        }
    }
}

// Zoom and View
// ============================================================================

void FancyIconPack::drawZoomIn(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    g.setColour(color);

    // Magnifying glass circle
    auto glassRadius = iconBounds.getWidth() * 0.35f;
    auto glassCentre = iconBounds.getCentre() - juce::Point<float>(glassRadius * 0.3f, glassRadius * 0.3f);
    g.drawEllipse(glassCentre.x - glassRadius, glassCentre.y - glassRadius,
                 glassRadius * 2, glassRadius * 2, stroke * 1.5f);

    // Handle
    auto handleStart = glassCentre + juce::Point<float>(glassRadius * 0.7f, glassRadius * 0.7f);
    auto handleEnd = iconBounds.getBottomRight() - juce::Point<float>(iconBounds.getWidth() * 0.15f, iconBounds.getHeight() * 0.15f);
    g.drawLine(handleStart.x, handleStart.y, handleEnd.x, handleEnd.y, stroke * 2.0f);

    // Plus sign inside
    auto plusSize = glassRadius * 0.6f;
    g.drawLine(glassCentre.x - plusSize * 0.5f, glassCentre.y,
              glassCentre.x + plusSize * 0.5f, glassCentre.y, stroke);
    g.drawLine(glassCentre.x, glassCentre.y - plusSize * 0.5f,
              glassCentre.x, glassCentre.y + plusSize * 0.5f, stroke);
}

void FancyIconPack::drawZoomOut(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    g.setColour(color);

    // Magnifying glass circle
    auto glassRadius = iconBounds.getWidth() * 0.35f;
    auto glassCentre = iconBounds.getCentre() - juce::Point<float>(glassRadius * 0.3f, glassRadius * 0.3f);
    g.drawEllipse(glassCentre.x - glassRadius, glassCentre.y - glassRadius,
                 glassRadius * 2, glassRadius * 2, stroke * 1.5f);

    // Handle
    auto handleStart = glassCentre + juce::Point<float>(glassRadius * 0.7f, glassRadius * 0.7f);
    auto handleEnd = iconBounds.getBottomRight() - juce::Point<float>(iconBounds.getWidth() * 0.15f, iconBounds.getHeight() * 0.15f);
    g.drawLine(handleStart.x, handleStart.y, handleEnd.x, handleEnd.y, stroke * 2.0f);

    // Minus sign inside
    auto minusSize = glassRadius * 0.6f;
    g.drawLine(glassCentre.x - minusSize * 0.5f, glassCentre.y,
              glassCentre.x + minusSize * 0.5f, glassCentre.y, stroke);
}

void FancyIconPack::drawFullscreen(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    g.setColour(color);

    auto cornerSize = iconBounds.getWidth() * 0.3f;

    // Top-left corner
    g.drawLine(iconBounds.getX(), iconBounds.getY(),
              iconBounds.getX() + cornerSize, iconBounds.getY(), stroke * 1.5f);
    g.drawLine(iconBounds.getX(), iconBounds.getY(),
              iconBounds.getX(), iconBounds.getY() + cornerSize, stroke * 1.5f);

    // Top-right corner
    g.drawLine(iconBounds.getRight() - cornerSize, iconBounds.getY(),
              iconBounds.getRight(), iconBounds.getY(), stroke * 1.5f);
    g.drawLine(iconBounds.getRight(), iconBounds.getY(),
              iconBounds.getRight(), iconBounds.getY() + cornerSize, stroke * 1.5f);

    // Bottom-left corner
    g.drawLine(iconBounds.getX(), iconBounds.getBottom() - cornerSize,
              iconBounds.getX(), iconBounds.getBottom(), stroke * 1.5f);
    g.drawLine(iconBounds.getX(), iconBounds.getBottom(),
              iconBounds.getX() + cornerSize, iconBounds.getBottom(), stroke * 1.5f);

    // Bottom-right corner
    g.drawLine(iconBounds.getRight() - cornerSize, iconBounds.getBottom(),
              iconBounds.getRight(), iconBounds.getBottom(), stroke * 1.5f);
    g.drawLine(iconBounds.getRight(), iconBounds.getBottom() - cornerSize,
              iconBounds.getRight(), iconBounds.getBottom(), stroke * 1.5f);
}

void FancyIconPack::drawExitFullscreen(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    g.setColour(color);

    auto cornerSize = iconBounds.getWidth() * 0.3f;
    auto inset = cornerSize * 0.5f;

    // Top-left corner (inward facing)
    g.drawLine(iconBounds.getX() + inset, iconBounds.getY() + inset,
              iconBounds.getX() + cornerSize, iconBounds.getY() + inset, stroke * 1.5f);
    g.drawLine(iconBounds.getX() + inset, iconBounds.getY() + inset,
              iconBounds.getX() + inset, iconBounds.getY() + cornerSize, stroke * 1.5f);

    // Top-right corner (inward facing)
    g.drawLine(iconBounds.getRight() - cornerSize, iconBounds.getY() + inset,
              iconBounds.getRight() - inset, iconBounds.getY() + inset, stroke * 1.5f);
    g.drawLine(iconBounds.getRight() - inset, iconBounds.getY() + inset,
              iconBounds.getRight() - inset, iconBounds.getY() + cornerSize, stroke * 1.5f);

    // Bottom-left corner (inward facing)
    g.drawLine(iconBounds.getX() + inset, iconBounds.getBottom() - cornerSize,
              iconBounds.getX() + inset, iconBounds.getBottom() - inset, stroke * 1.5f);
    g.drawLine(iconBounds.getX() + inset, iconBounds.getBottom() - inset,
              iconBounds.getX() + cornerSize, iconBounds.getBottom() - inset, stroke * 1.5f);

    // Bottom-right corner (inward facing)
    g.drawLine(iconBounds.getRight() - cornerSize, iconBounds.getBottom() - inset,
              iconBounds.getRight() - inset, iconBounds.getBottom() - inset, stroke * 1.5f);
    g.drawLine(iconBounds.getRight() - inset, iconBounds.getBottom() - cornerSize,
              iconBounds.getRight() - inset, iconBounds.getBottom() - inset, stroke * 1.5f);
}

void FancyIconPack::drawTab(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    g.setColour(color);

    // Tab shape - rounded rectangle at top
    auto tabHeight = iconBounds.getHeight() * 0.4f;
    auto tabBounds = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getY(),
                                          iconBounds.getWidth() * 0.6f, tabHeight);

    juce::Path tab;
    tab.addRoundedRectangle(tabBounds.getX(), tabBounds.getY(), tabBounds.getWidth(), tabBounds.getHeight(),
                           3.0f, 3.0f, true, true, false, false);
    g.strokePath(tab, juce::PathStrokeType(stroke));

    // Content area below
    auto contentBounds = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getY() + tabHeight,
                                              iconBounds.getWidth(), iconBounds.getHeight() - tabHeight);
    g.drawRoundedRectangle(contentBounds, 2.0f, stroke);
}

// Control Types
// ============================================================================

void FancyIconPack::drawSliderHorizontal(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Track
    auto trackY = iconBounds.getCentreY();
    g.setColour(color.withAlpha(0.4f));
    g.drawLine(iconBounds.getX(), trackY, iconBounds.getRight(), trackY, stroke * 2.0f);

    // Thumb
    auto thumbX = iconBounds.getX() + iconBounds.getWidth() * 0.7f; // Position at 70%
    auto thumbSize = iconBounds.getHeight() * 0.6f;
    auto thumbBounds = juce::Rectangle<float>(thumbX - thumbSize * 0.5f, trackY - thumbSize * 0.5f,
                                            thumbSize, thumbSize);

    g.setColour(color);
    g.fillEllipse(thumbBounds);
    g.setColour(color.darker(0.3f));
    g.drawEllipse(thumbBounds, stroke);
}

void FancyIconPack::drawSliderVertical(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Track
    auto trackX = iconBounds.getCentreX();
    g.setColour(color.withAlpha(0.4f));
    g.drawLine(trackX, iconBounds.getY(), trackX, iconBounds.getBottom(), stroke * 2.0f);

    // Thumb
    auto thumbY = iconBounds.getY() + iconBounds.getHeight() * 0.3f; // Position at 30%
    auto thumbSize = iconBounds.getWidth() * 0.6f;
    auto thumbBounds = juce::Rectangle<float>(trackX - thumbSize * 0.5f, thumbY - thumbSize * 0.5f,
                                            thumbSize, thumbSize);

    g.setColour(color);
    g.fillEllipse(thumbBounds);
    g.setColour(color.darker(0.3f));
    g.drawEllipse(thumbBounds, stroke);
}

void FancyIconPack::drawKnob(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    auto centre = iconBounds.getCentre();
    auto radius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.4f;

    // Knob body
    g.setColour(color.withAlpha(0.8f));
    g.fillEllipse(centre.x - radius, centre.y - radius, radius * 2, radius * 2);

    g.setColour(color);
    g.drawEllipse(centre.x - radius, centre.y - radius, radius * 2, radius * 2, stroke);

    // Pointer line (at 45 degrees)
    auto angle = juce::MathConstants<float>::pi * 0.25f; // 45 degrees
    auto pointerEnd = centre + juce::Point<float>(radius * 0.7f * std::cos(angle),
                                                 radius * 0.7f * std::sin(angle));

    g.setColour(color.darker(0.5f));
    g.drawLine(centre.x, centre.y, pointerEnd.x, pointerEnd.y, stroke * 1.5f);
}

void FancyIconPack::drawSwitch(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Switch track
    auto trackBounds = iconBounds.withSizeKeepingCentre(iconBounds.getWidth(), iconBounds.getHeight() * 0.5f);
    g.setColour(color.withAlpha(0.3f));
    g.fillRoundedRectangle(trackBounds, trackBounds.getHeight() * 0.5f);

    g.setColour(color);
    g.drawRoundedRectangle(trackBounds, trackBounds.getHeight() * 0.5f, stroke);

    // Switch thumb (positioned to show "on" state)
    auto thumbSize = trackBounds.getHeight() * 0.8f;
    auto thumbX = trackBounds.getRight() - thumbSize * 0.6f; // Positioned for "on"
    auto thumbBounds = juce::Rectangle<float>(thumbX - thumbSize * 0.5f, trackBounds.getCentreY() - thumbSize * 0.5f,
                                            thumbSize, thumbSize);

    g.setColour(color);
    g.fillEllipse(thumbBounds);
}

void FancyIconPack::drawToggleOn(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Filled square with checkmark
    g.setColour(color);
    g.fillRoundedRectangle(iconBounds, 3.0f);

    // Checkmark
    g.setColour(juce::Colours::white);
    auto checkSize = iconBounds.getWidth() * 0.6f;
    auto checkCentre = iconBounds.getCentre();

    juce::Path check;
    check.startNewSubPath(checkCentre.x - checkSize * 0.3f, checkCentre.y);
    check.lineTo(checkCentre.x - checkSize * 0.1f, checkCentre.y + checkSize * 0.2f);
    check.lineTo(checkCentre.x + checkSize * 0.3f, checkCentre.y - checkSize * 0.2f);

    g.strokePath(check, juce::PathStrokeType(stroke * 1.5f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
}

void FancyIconPack::drawToggleOff(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Empty square
    g.setColour(color);
    g.drawRoundedRectangle(iconBounds, 3.0f, stroke * 1.5f);
}

void FancyIconPack::drawCheckbox(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Square with slightly rounded corners
    g.setColour(color);
    g.drawRoundedRectangle(iconBounds, 2.0f, stroke * 1.5f);

    // Partial checkmark to indicate it's checkable
    auto checkSize = iconBounds.getWidth() * 0.4f;
    auto checkCentre = iconBounds.getCentre();

    g.setColour(color.withAlpha(0.5f));
    juce::Path check;
    check.startNewSubPath(checkCentre.x - checkSize * 0.3f, checkCentre.y);
    check.lineTo(checkCentre.x - checkSize * 0.1f, checkCentre.y + checkSize * 0.2f);
    check.lineTo(checkCentre.x + checkSize * 0.3f, checkCentre.y - checkSize * 0.2f);

    g.strokePath(check, juce::PathStrokeType(stroke, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
}

void FancyIconPack::drawRadioOn(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    auto centre = iconBounds.getCentre();
    auto radius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.5f;

    // Outer circle
    g.setColour(color);
    g.drawEllipse(centre.x - radius, centre.y - radius, radius * 2, radius * 2, stroke * 1.5f);

    // Inner filled circle (selected state)
    auto innerRadius = radius * 0.5f;
    g.fillEllipse(centre.x - innerRadius, centre.y - innerRadius, innerRadius * 2, innerRadius * 2);
}

void FancyIconPack::drawRadioOff(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    auto centre = iconBounds.getCentre();
    auto radius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.5f;

    // Outer circle only
    g.setColour(color);
    g.drawEllipse(centre.x - radius, centre.y - radius, radius * 2, radius * 2, stroke * 1.5f);
}

void FancyIconPack::drawContextMenu(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Menu background
    g.setColour(color.withAlpha(0.2f));
    g.fillRoundedRectangle(iconBounds, 3.0f);

    g.setColour(color);
    g.drawRoundedRectangle(iconBounds, 3.0f, stroke);

    // Menu items (horizontal lines)
    auto itemHeight = iconBounds.getHeight() / 5.0f;
    auto itemPadding = iconBounds.getWidth() * 0.2f;

    for (int i = 1; i < 5; ++i)
    {
        auto y = iconBounds.getY() + i * itemHeight;
        g.drawLine(iconBounds.getX() + itemPadding, y, iconBounds.getRight() - itemPadding, y, stroke);
    }
}
