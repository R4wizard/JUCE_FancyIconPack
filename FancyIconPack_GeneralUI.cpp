#include "FancyIconPack.h"

// ============================================================================
// GENERAL UI / WORKFLOW ICONS IMPLEMENTATION
// ============================================================================

void FancyIconPack::drawCopy(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    auto rectSize = iconBounds.getWidth() * 0.35f;
    auto offset = rectSize * 0.3f;

    // Back rectangle
    auto backRect = juce::Rectangle<float>(iconBounds.getX() + offset, iconBounds.getY() + offset, rectSize, rectSize);
    g.setColour(color.withAlpha(0.6f));
    g.drawRoundedRectangle(backRect, 2.0f, stroke);

    // Front rectangle
    auto frontRect = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getY(), rectSize, rectSize);
    g.setColour(color);
    g.drawRoundedRectangle(frontRect, 2.0f, stroke);
}

void FancyIconPack::drawEdit(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    juce::Path pencil;
    auto size = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight());
    auto tip = iconBounds.getBottomLeft() + juce::Point<float>(size * 0.15f, -size * 0.15f);
    auto top = iconBounds.getTopRight() + juce::Point<float>(-size * 0.15f, size * 0.15f);

    // Pencil body
    pencil.startNewSubPath(tip);
    pencil.lineTo(top + juce::Point<float>(-size * 0.1f, size * 0.1f));
    pencil.lineTo(top + juce::Point<float>(0, size * 0.15f));
    pencil.lineTo(tip + juce::Point<float>(size * 0.05f, 0));
    pencil.closeSubPath();

    g.setColour(color);
    g.fillPath(pencil);

    // Edit line at tip
    g.drawLine(tip.x - size * 0.05f, tip.y + size * 0.05f,
              tip.x - size * 0.15f, tip.y + size * 0.15f, stroke * 1.5f);
}

void FancyIconPack::drawSave(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Main disk body
    g.setColour(color);
    g.drawRoundedRectangle(iconBounds, 3.0f, stroke);

    // Top notch (cut corner)
    auto notchSize = iconBounds.getWidth() * 0.2f;
    juce::Path notch;
    notch.startNewSubPath(iconBounds.getRight() - notchSize, iconBounds.getY());
    notch.lineTo(iconBounds.getRight(), iconBounds.getY() + notchSize);
    g.strokePath(notch, createStroke(stroke));

    // Label area
    auto labelBounds = iconBounds.removeFromTop(iconBounds.getHeight() * 0.3f).reduced(stroke * 2);
    g.fillRoundedRectangle(labelBounds, 2.0f);

    // Metal slider
    auto sliderBounds = juce::Rectangle<float>(iconBounds.getCentreX() - iconBounds.getWidth() * 0.25f,
                                              iconBounds.getCentreY() + iconBounds.getHeight() * 0.1f,
                                              iconBounds.getWidth() * 0.5f, stroke * 2);
    g.fillRoundedRectangle(sliderBounds, stroke);
}

void FancyIconPack::drawLoad(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Folder body
    auto folderBounds = iconBounds.removeFromBottom(iconBounds.getHeight() * 0.75f);
    g.setColour(color);
    g.drawRoundedRectangle(folderBounds, 2.0f, stroke);

    // Folder tab
    auto tabWidth = iconBounds.getWidth() * 0.4f;
    auto tabHeight = iconBounds.getHeight() * 0.25f;
    auto tabBounds = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getY(), tabWidth, tabHeight);
    g.drawRoundedRectangle(tabBounds, 2.0f, stroke);

    // Connect tab to body
    g.drawLine(juce::Line<float>(tabBounds.getBottomLeft(), folderBounds.getTopLeft()), stroke);
    g.drawLine(juce::Line<float>(tabBounds.getBottomRight(), folderBounds.getTopLeft() + juce::Point<float>(tabWidth, 0)), stroke);
}

void FancyIconPack::drawNewPreset(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Document outline
    g.setColour(color);
    g.drawRoundedRectangle(iconBounds, 2.0f, stroke);

    // Plus sign in center
    auto centre = iconBounds.getCentre();
    auto plusSize = iconBounds.getWidth() * 0.25f;

    // Horizontal line
    g.fillRoundedRectangle(centre.x - plusSize, centre.y - stroke * 0.5f,
                          plusSize * 2, stroke, stroke * 0.5f);

    // Vertical line
    g.fillRoundedRectangle(centre.x - stroke * 0.5f, centre.y - plusSize,
                          stroke, plusSize * 2, stroke * 0.5f);
}

void FancyIconPack::drawRename(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Text cursor
    auto cursorHeight = iconBounds.getHeight() * 0.8f;
    auto cursorX = iconBounds.getCentreX();
    auto cursorY = iconBounds.getCentreY() - cursorHeight * 0.5f;

    g.setColour(color);
    g.fillRoundedRectangle(cursorX - stroke * 0.5f, cursorY, stroke, cursorHeight, stroke * 0.5f);

    // Text selection boxes
    auto boxWidth = iconBounds.getWidth() * 0.15f;
    auto boxHeight = stroke * 2;

    // Three text lines
    for (int i = 0; i < 3; ++i)
    {
        auto y = cursorY + (cursorHeight / 4.0f) * (i + 1);
        auto width = boxWidth * (1.2f - i * 0.2f); // Varying widths

        g.setColour(color.withAlpha(0.4f));
        g.fillRoundedRectangle(cursorX + stroke * 2, y - boxHeight * 0.5f, width, boxHeight, 1.0f);
    }
}

void FancyIconPack::drawDelete(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Trash can body
    auto canBounds = iconBounds.removeFromBottom(iconBounds.getHeight() * 0.8f);
    canBounds = canBounds.reduced(canBounds.getWidth() * 0.1f, 0);

    g.setColour(color);
    g.drawRoundedRectangle(canBounds, 2.0f, stroke);

    // Lid
    auto lidBounds = juce::Rectangle<float>(iconBounds.getX(), canBounds.getY() - stroke * 2,
                                           iconBounds.getWidth(), stroke * 2);
    g.fillRoundedRectangle(lidBounds, stroke);

    // Handle
    auto handleWidth = iconBounds.getWidth() * 0.3f;
    auto handleBounds = juce::Rectangle<float>(iconBounds.getCentreX() - handleWidth * 0.5f,
                                              lidBounds.getY() - stroke * 1.5f,
                                              handleWidth, stroke);
    g.fillRoundedRectangle(handleBounds, stroke * 0.5f);

    // Vertical lines inside
    auto lineSpacing = canBounds.getWidth() * 0.25f;
    for (int i = 0; i < 3; ++i)
    {
        auto x = canBounds.getX() + lineSpacing + i * lineSpacing;
        g.drawLine(x, canBounds.getY() + canBounds.getHeight() * 0.2f,
                  x, canBounds.getBottom() - canBounds.getHeight() * 0.2f, stroke * 0.8f);
    }
}

void FancyIconPack::drawPaste(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Clipboard base
    auto clipboardBounds = iconBounds.reduced(iconBounds.getWidth() * 0.1f, 0);
    g.setColour(color);
    g.drawRoundedRectangle(clipboardBounds, 2.0f, stroke);

    // Clipboard clip at top
    auto clipWidth = iconBounds.getWidth() * 0.3f;
    auto clipHeight = iconBounds.getHeight() * 0.15f;
    auto clipBounds = juce::Rectangle<float>(iconBounds.getCentreX() - clipWidth * 0.5f,
                                            iconBounds.getY() - clipHeight * 0.3f,
                                            clipWidth, clipHeight);
    g.fillRoundedRectangle(clipBounds, 2.0f);

    // Document lines inside
    auto lineWidth = clipboardBounds.getWidth() * 0.6f;
    auto lineStart = clipboardBounds.getX() + (clipboardBounds.getWidth() - lineWidth) * 0.5f;

    for (int i = 0; i < 3; ++i)
    {
        auto y = clipboardBounds.getY() + clipboardBounds.getHeight() * (0.3f + i * 0.15f);
        g.fillRoundedRectangle(lineStart, y, lineWidth * (1.0f - i * 0.1f), stroke * 0.8f, stroke * 0.4f);
    }
}

void FancyIconPack::drawDuplicate(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    auto rectSize = iconBounds.getWidth() * 0.4f;
    auto offset = rectSize * 0.25f;

    // Back rectangle (more visible than copy)
    auto backRect = juce::Rectangle<float>(iconBounds.getX() + offset, iconBounds.getY() + offset, rectSize, rectSize);
    g.setColour(color.withAlpha(0.8f));
    g.fillRoundedRectangle(backRect, 2.0f);
    g.setColour(color);
    g.drawRoundedRectangle(backRect, 2.0f, stroke);

    // Front rectangle
    auto frontRect = juce::Rectangle<float>(iconBounds.getX(), iconBounds.getY(), rectSize, rectSize);
    g.fillRoundedRectangle(frontRect, 2.0f);
    g.setColour(color.contrasting(0.8f));
    g.drawRoundedRectangle(frontRect, 2.0f, stroke * 0.8f);
}

void FancyIconPack::drawUndo(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);
    auto centre = iconBounds.getCentre();

    juce::Path arrow;
    auto radius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.35f;
    float startAngle = juce::MathConstants<float>::pi * 1.5f;
    float endAngle   = juce::MathConstants<float>::pi * 3.0f;

    arrow.addCentredArc(centre.x, centre.y, radius, radius, 0.0f,
                        startAngle, endAngle, true); // anticlockwise

    g.setColour(color);
    g.strokePath(arrow, createStroke(stroke));

	// Get actual start point of arc
	auto arrowTip = juce::Point<float>(centre.x + radius * std::cos(endAngle),
	                                      centre.y + radius * std::sin(endAngle));

	// Correct tangent direction for clockwise arc
	float tangentAngle = juce::MathConstants<float>::halfPi + 0.3f;

	// Arrowhead dimensions
	float headLength = radius * 0.7f;
	float headWidth  = headLength * 1.0f;

	// Build wings
	juce::Point<float> wing1(
		arrowTip.x - headLength * std::cos(tangentAngle) + headWidth * std::sin(tangentAngle),
		arrowTip.y - headLength * std::sin(tangentAngle) - headWidth * std::cos(tangentAngle));

	juce::Point<float> wing2(
		arrowTip.x - headLength * std::cos(tangentAngle) - headWidth * std::sin(tangentAngle),
		arrowTip.y - headLength * std::sin(tangentAngle) + headWidth * std::cos(tangentAngle));

	// Draw arrowhead lines
	g.drawLine(arrowTip.x, arrowTip.y, wing1.x, wing1.y, stroke);
	g.drawLine(arrowTip.x, arrowTip.y, wing2.x, wing2.y, stroke);
}

void FancyIconPack::drawRedo(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);
    auto centre = iconBounds.getCentre();

    juce::Path arrow;
    auto radius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.35f;
    float startAngle = juce::MathConstants<float>::pi;
    float endAngle   = juce::MathConstants<float>::pi * 2.5f;

    arrow.addCentredArc(centre.x, centre.y, radius, radius, 0.0f,
                        startAngle, endAngle, true);

    g.setColour(color);
    g.strokePath(arrow, createStroke(stroke));

	// Get actual endpoint of arc
	auto arrowTip = arrow.getCurrentPosition();

	// Correct tangent direction for clockwise arc
	float tangentAngle = juce::MathConstants<float>::halfPi - 0.3f;

	// Arrowhead dimensions
	float headLength = radius * 0.7f;
	float headWidth  = headLength * 1.0f;

	// Build wings
	juce::Point<float> wing1(
		arrowTip.x - headLength * std::cos(tangentAngle) + headWidth * std::sin(tangentAngle),
		arrowTip.y - headLength * std::sin(tangentAngle) - headWidth * std::cos(tangentAngle));

	juce::Point<float> wing2(
		arrowTip.x - headLength * std::cos(tangentAngle) - headWidth * std::sin(tangentAngle),
		arrowTip.y - headLength * std::sin(tangentAngle) + headWidth * std::cos(tangentAngle));

	// Draw arrowhead lines
	g.drawLine(arrowTip.x, arrowTip.y, wing1.x, wing1.y, stroke);
	g.drawLine(arrowTip.x, arrowTip.y, wing2.x, wing2.y, stroke);
}

void FancyIconPack::drawSettings(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto centre = iconBounds.getCentre();
    auto outerRadius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.45f;
    auto innerRadius = outerRadius * 0.4f;

    juce::Path gear;
    const int teeth = 8;
    const float angleStep = juce::MathConstants<float>::twoPi / teeth;

    for (int i = 0; i < teeth; ++i)
    {
        float angle = i * angleStep;
        float nextAngle = (i + 1) * angleStep;

        // Outer tooth points
        auto p1 = centre + juce::Point<float>(std::cos(angle - angleStep * 0.1f) * outerRadius,
                                             std::sin(angle - angleStep * 0.1f) * outerRadius);
        auto p2 = centre + juce::Point<float>(std::cos(angle + angleStep * 0.1f) * outerRadius,
                                             std::sin(angle + angleStep * 0.1f) * outerRadius);

        // Inner valley points
        auto p3 = centre + juce::Point<float>(std::cos(nextAngle - angleStep * 0.4f) * innerRadius,
                                             std::sin(nextAngle - angleStep * 0.4f) * innerRadius);
        auto p4 = centre + juce::Point<float>(std::cos(angle + angleStep * 0.4f) * innerRadius,
                                             std::sin(angle + angleStep * 0.4f) * innerRadius);

        if (i == 0)
            gear.startNewSubPath(p1);
        else
            gear.lineTo(p1);

        gear.lineTo(p2);
        gear.lineTo(p3);
        gear.lineTo(p4);
    }
    gear.closeSubPath();

    // Center hole
    gear.addEllipse(centre.x - innerRadius * 0.4f, centre.y - innerRadius * 0.4f,
                   innerRadius * 0.8f, innerRadius * 0.8f);
    gear.setUsingNonZeroWinding(false);

    g.setColour(color);
    g.fillPath(gear);
}

void FancyIconPack::drawBurgerMenu(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds, 0.15f);

    auto lineSpacing = iconBounds.getHeight() / 4.0f;
    auto lineWidth = iconBounds.getWidth();

    g.setColour(color);

	// split icon bounds into three horizontal lines
	auto lineHeightArea = iconBounds.getHeight() / 5.0f;

	g.fillRoundedRectangle(
		iconBounds.getX(),
		std::floor(iconBounds.getY() + (lineHeightArea * 0.5f)),
		lineWidth,
		stroke,
		stroke * 0.5f
	);

	g.fillRoundedRectangle(
		iconBounds.getX(),
		std::floor(iconBounds.getY() + (lineHeightArea * 2.5f)),
		lineWidth,
		stroke,
		stroke * 0.5f
	);

	g.fillRoundedRectangle(
		iconBounds.getX(),
		std::floor(iconBounds.getY() + (lineHeightArea * 4.5f)),
		lineWidth,
		stroke,
		stroke * 0.5f
	);
}

void FancyIconPack::drawDropdown(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto centre = iconBounds.getCentre();
    auto size = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.5f;

    juce::Path triangle;
    triangle.startNewSubPath(centre.x, centre.y + size * 0.3f);
    triangle.lineTo(centre.x - size * 0.5f, centre.y - size * 0.3f);
    triangle.lineTo(centre.x + size * 0.5f, centre.y - size * 0.3f);
    triangle.closeSubPath();

    g.setColour(color);
    g.fillPath(triangle);
}

void FancyIconPack::drawSearch(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    auto glassRadius = iconBounds.getWidth() * 0.3f;
    auto glassCentre = iconBounds.getCentre() - juce::Point<float>(glassRadius * 0.3f, glassRadius * 0.3f);

    g.setColour(color);

    // Magnifying glass circle
    g.drawEllipse(glassCentre.x - glassRadius, glassCentre.y - glassRadius,
                 glassRadius * 2, glassRadius * 2, stroke);

    // Handle
    auto handleStart = glassCentre + juce::Point<float>(glassRadius * 0.7f, glassRadius * 0.7f);
    auto handleEnd = handleStart + juce::Point<float>(glassRadius * 0.8f, glassRadius * 0.8f);
    g.drawLine(juce::Line<float>(handleStart, handleEnd), stroke * 1.2f);
}

void FancyIconPack::drawClose(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    g.setColour(color);

    // Two diagonal lines forming an X
    g.drawLine(juce::Line<float>(iconBounds.getTopLeft(), iconBounds.getBottomRight()), stroke);
    g.drawLine(juce::Line<float>(iconBounds.getTopRight(), iconBounds.getBottomLeft()), stroke);
}

void FancyIconPack::drawExpand(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    g.setColour(color);
    g.drawRect(iconBounds, stroke);

    // Corner arrows
    auto arrowSize = iconBounds.getWidth() * 0.2f;

    // Top-left arrow
    juce::Path tlArrow;
    tlArrow.startNewSubPath(iconBounds.getTopLeft());
    tlArrow.lineTo(iconBounds.getTopLeft() + juce::Point<float>(arrowSize, 0));
    tlArrow.startNewSubPath(iconBounds.getTopLeft());
    tlArrow.lineTo(iconBounds.getTopLeft() + juce::Point<float>(0, arrowSize));

    // Bottom-right arrow
    juce::Path brArrow;
    brArrow.startNewSubPath(iconBounds.getBottomRight());
    brArrow.lineTo(iconBounds.getBottomRight() - juce::Point<float>(arrowSize, 0));
    brArrow.startNewSubPath(iconBounds.getBottomRight());
    brArrow.lineTo(iconBounds.getBottomRight() - juce::Point<float>(0, arrowSize));

    g.strokePath(tlArrow, createStroke(stroke));
    g.strokePath(brArrow, createStroke(stroke));
}

void FancyIconPack::drawCollapse(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);
    auto centre = iconBounds.getCentre();
    auto innerSize = iconBounds.getWidth() * 0.6f;
    auto innerBounds = juce::Rectangle<float>(centre.x - innerSize * 0.5f, centre.y - innerSize * 0.5f,
                                             innerSize, innerSize);

    g.setColour(color);
    g.drawRect(innerBounds, stroke);

    // Corner arrows pointing inward
    auto arrowSize = iconBounds.getWidth() * 0.15f;

    // Top-left arrow
    auto tlStart = iconBounds.getTopLeft();
    juce::Path tlArrow;
    tlArrow.startNewSubPath(tlStart + juce::Point<float>(arrowSize, 0));
    tlArrow.lineTo(tlStart);
    tlArrow.lineTo(tlStart + juce::Point<float>(0, arrowSize));

    // Bottom-right arrow
    auto brStart = iconBounds.getBottomRight();
    juce::Path brArrow;
    brArrow.startNewSubPath(brStart - juce::Point<float>(arrowSize, 0));
    brArrow.lineTo(brStart);
    brArrow.lineTo(brStart - juce::Point<float>(0, arrowSize));

    g.strokePath(tlArrow, createStroke(stroke));
    g.strokePath(brArrow, createStroke(stroke));
}

void FancyIconPack::drawInfo(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);
    auto centre = iconBounds.getCentre();
    auto radius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.45f;

    g.setColour(color);

    // Circle outline
    g.drawEllipse(centre.x - radius, centre.y - radius, radius * 2, radius * 2, stroke);

    // Dot at top
    auto dotRadius = stroke * 1.2f;
    auto dotY = centre.y - radius * 0.4f;
    g.fillEllipse(centre.x - dotRadius, dotY - dotRadius, dotRadius * 2, dotRadius * 2);

    // Vertical line below
    auto lineStart = centre.y - radius * 0.1f;
    auto lineEnd = centre.y + radius * 0.4f;
    g.fillRoundedRectangle(centre.x - stroke * 0.6f, lineStart, stroke * 1.2f, lineEnd - lineStart, stroke * 0.6f);
}

void FancyIconPack::drawHelp(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);
    auto centre = iconBounds.getCentre();
    auto radius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.45f;

    g.setColour(color);

    // Circle outline
    g.drawEllipse(centre.x - radius, centre.y - radius, radius * 2, radius * 2, stroke);

    // Question mark path
    juce::Path questionPath;
    auto topY = centre.y - radius * 0.4f;
    auto bottomY = centre.y + radius * 0.1f;
    auto leftX = centre.x - radius * 0.25f;
    auto rightX = centre.x + radius * 0.25f;

    // Top curve
    questionPath.startNewSubPath(leftX, topY + radius * 0.15f);
    questionPath.quadraticTo(leftX, topY, centre.x, topY);
    questionPath.quadraticTo(rightX, topY, rightX, topY + radius * 0.15f);
    // Down and hook
    questionPath.quadraticTo(rightX, centre.y - radius * 0.1f, centre.x, centre.y - radius * 0.1f);
    questionPath.lineTo(centre.x, bottomY);

    g.strokePath(questionPath, createStroke(stroke));

    // Dot below
    auto dotY = centre.y + radius * 0.35f;
    auto dotSize = stroke * 1.5f;
    g.fillEllipse(centre.x - dotSize * 0.5f, dotY - dotSize * 0.5f, dotSize, dotSize);
}

void FancyIconPack::drawWarning(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);
    auto centre = iconBounds.getCentre();
    auto size = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.8f;

    // Triangle outline
    juce::Path triangle;
    triangle.startNewSubPath(centre.x, iconBounds.getY()); // Top point
    triangle.lineTo(iconBounds.getX(), iconBounds.getBottom()); // Bottom left
    triangle.lineTo(iconBounds.getRight(), iconBounds.getBottom()); // Bottom right
    triangle.closeSubPath();

    g.setColour(color);
    g.strokePath(triangle, createStroke(stroke));

    // Exclamation mark
    auto lineHeight = size * 0.4f;
    auto lineY = centre.y - lineHeight * 0.3f;
    g.fillRoundedRectangle(centre.x - stroke * 0.6f, lineY, stroke * 1.2f, lineHeight, stroke * 0.6f);

    // Dot
    auto dotY = centre.y + size * 0.25f;
    auto dotSize = stroke * 1.5f;
    g.fillEllipse(centre.x - dotSize * 0.5f, dotY - dotSize * 0.5f, dotSize, dotSize);
}

void FancyIconPack::drawError(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);
    auto centre = iconBounds.getCentre();
    auto radius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.45f;

    g.setColour(color);

    // Circle outline
    g.drawEllipse(centre.x - radius, centre.y - radius, radius * 2, radius * 2, stroke);

    // X inside circle
    auto crossSize = radius * 0.6f;
    g.drawLine(centre.x - crossSize, centre.y - crossSize, centre.x + crossSize, centre.y + crossSize, stroke * 1.2f);
    g.drawLine(centre.x + crossSize, centre.y - crossSize, centre.x - crossSize, centre.y + crossSize, stroke * 1.2f);
}

void FancyIconPack::drawCheck(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Checkmark path
    juce::Path checkmark;
    auto size = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight());
    auto startX = iconBounds.getX() + size * 0.2f;
    auto middleX = iconBounds.getCentreX();
    auto endX = iconBounds.getRight() - size * 0.1f;
    auto startY = iconBounds.getCentreY();
    auto middleY = iconBounds.getBottom() - size * 0.3f;
    auto endY = iconBounds.getY() + size * 0.2f;

    checkmark.startNewSubPath(startX, startY);
    checkmark.lineTo(middleX, middleY);
    checkmark.lineTo(endX, endY);

    g.setColour(color);
    g.strokePath(checkmark, createStroke(stroke * 1.2f));
}

void FancyIconPack::drawPlus(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);
    auto centre = iconBounds.getCentre();
    auto size = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.4f;

    g.setColour(color);

    // Horizontal line
    g.fillRoundedRectangle(
		centre.x - size,
		centre.y - stroke * 0.5f,
		size * 2,
		stroke,
		stroke * 0.5f
	);

    // Vertical line
    g.fillRoundedRectangle(
		centre.x - stroke * 0.5f,
		centre.y - size,
		stroke,
		size * 2,
		stroke * 0.5f
	);
}

void FancyIconPack::drawMinus(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);
    auto centre = iconBounds.getCentre();
    auto size = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.4f;

    g.setColour(color);

    // Horizontal line
    g.fillRoundedRectangle(centre.x - size, centre.y - stroke * 0.5f,
                          size * 2, stroke, stroke * 0.5f);
}

void FancyIconPack::drawArrowUp(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto centre = iconBounds.getCentre();
    auto size = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.4f;

    juce::Path arrow;
    arrow.startNewSubPath(centre.x, centre.y - size); // Top point
    arrow.lineTo(centre.x - size * 0.7f, centre.y); // Left point
    arrow.lineTo(centre.x + size * 0.7f, centre.y); // Right point
    arrow.closeSubPath();

    g.setColour(color);
    g.fillPath(arrow);
}

void FancyIconPack::drawArrowDown(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto centre = iconBounds.getCentre();
    auto size = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.4f;

    juce::Path arrow;
    arrow.startNewSubPath(centre.x, centre.y + size); // Bottom point
    arrow.lineTo(centre.x - size * 0.7f, centre.y); // Left point
    arrow.lineTo(centre.x + size * 0.7f, centre.y); // Right point
    arrow.closeSubPath();

    g.setColour(color);
    g.fillPath(arrow);
}

void FancyIconPack::drawArrowLeft(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto centre = iconBounds.getCentre();
    auto size = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.4f;

    juce::Path arrow;
    arrow.startNewSubPath(centre.x - size, centre.y); // Left point
    arrow.lineTo(centre.x, centre.y - size * 0.7f); // Top point
    arrow.lineTo(centre.x, centre.y + size * 0.7f); // Bottom point
    arrow.closeSubPath();

    g.setColour(color);
    g.fillPath(arrow);
}

void FancyIconPack::drawArrowRight(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto centre = iconBounds.getCentre();
    auto size = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.4f;

    juce::Path arrow;
    arrow.startNewSubPath(centre.x + size, centre.y); // Right point
    arrow.lineTo(centre.x, centre.y - size * 0.7f); // Top point
    arrow.lineTo(centre.x, centre.y + size * 0.7f); // Bottom point
    arrow.closeSubPath();

    g.setColour(color);
    g.fillPath(arrow);
}
