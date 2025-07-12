#include "FancyIconPack.h"

// ============================================================================
// ADVANCED UI / WORKFLOW FEATURES IMPLEMENTATION - PART 2
// ============================================================================

// UI Layout (Part 2)
// ============================================================================

void FancyIconPack::drawContextPopup(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Context menu popup with cursor
    auto menuHeight = iconBounds.getHeight() * 0.7f;
    auto menuWidth = iconBounds.getWidth() * 0.75f;
    auto menuBounds = juce::Rectangle<float>(iconBounds.getRight() - menuWidth, iconBounds.getY(),
                                           menuWidth, menuHeight);

    // Menu background
    g.setColour(color);
    g.fillRoundedRectangle(menuBounds, stroke);
    g.drawRoundedRectangle(menuBounds, stroke, stroke * 0.8f);

    // Menu items (horizontal lines)
    auto itemCount = 4;
    auto itemHeight = menuHeight / (itemCount + 1);
    auto contentArea = menuBounds.reduced(stroke * 1.5f);

    g.setColour(color.withAlpha(0.7f));
    for (int i = 0; i < itemCount; ++i)
    {
        auto itemY = contentArea.getY() + itemHeight * (i + 0.5f);
        auto itemWidth = contentArea.getWidth() * (0.9f - i * 0.1f); // Varying widths

        if (i == 1) // Highlight one item
        {
            g.setColour(color.brighter(0.3f));
            g.fillRoundedRectangle(contentArea.getX() - stroke * 0.5f, itemY - stroke,
                                  contentArea.getWidth() + stroke, stroke * 2, stroke * 0.5f);
            g.setColour(color.darker(0.3f));
        }

        g.drawLine(contentArea.getX(), itemY, contentArea.getX() + itemWidth, itemY, stroke * 0.8f);

        if (i == 1)
            g.setColour(color.withAlpha(0.7f));
    }

    // Separator line
    auto separatorY = contentArea.getY() + itemHeight * 2.2f;
    g.setColour(color.withAlpha(0.4f));
    g.drawLine(contentArea.getX(), separatorY, contentArea.getRight(), separatorY, stroke * 0.4f);

    // Mouse cursor/pointer
    auto cursorSize = iconBounds.getWidth() * 0.3f;
    auto cursorX = iconBounds.getX() + stroke;
    auto cursorY = iconBounds.getBottom() - cursorSize - stroke;

    g.setColour(color.brighter(0.2f));

    // Cursor shape (arrow pointer)
    juce::Path cursor;
    cursor.startNewSubPath(cursorX, cursorY);
    cursor.lineTo(cursorX, cursorY + cursorSize);
    cursor.lineTo(cursorX + cursorSize * 0.3f, cursorY + cursorSize * 0.7f);
    cursor.lineTo(cursorX + cursorSize * 0.5f, cursorY + cursorSize * 0.8f);
    cursor.lineTo(cursorX + cursorSize * 0.7f, cursorY + cursorSize * 0.5f);
    cursor.lineTo(cursorX + cursorSize * 0.4f, cursorY + cursorSize * 0.4f);
    cursor.closeSubPath();

    g.fillPath(cursor);
    g.strokePath(cursor, createStroke(stroke * 0.6f));

    // Right-click indication (small "R" or dots)
    g.setColour(color.withAlpha(0.6f));
    auto clickIndicatorX = cursorX + cursorSize * 0.8f;
    auto clickIndicatorY = cursorY + cursorSize * 0.2f;
    auto dotRadius = stroke * 0.4f;

    // Three dots to indicate right-click context
    for (int i = 0; i < 3; ++i)
    {
        auto dotY = clickIndicatorY + i * stroke * 1.2f;
        g.fillEllipse(clickIndicatorX - dotRadius, dotY - dotRadius, dotRadius * 2, dotRadius * 2);
    }
}

// Theme and Appearance
// ============================================================================

void FancyIconPack::drawThemeLight(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Sun icon for light theme
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto sunRadius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.2f;

    // Sun center
    g.setColour(color);
    g.fillEllipse(centerX - sunRadius, centerY - sunRadius, sunRadius * 2, sunRadius * 2);

    // Sun rays
    auto rayCount = 8;
    auto rayInnerRadius = sunRadius * 1.4f;
    auto rayOuterRadius = sunRadius * 2.0f;

    for (int i = 0; i < rayCount; ++i)
    {
        auto angle = (i / static_cast<float>(rayCount)) * juce::MathConstants<float>::twoPi;
        auto innerX = centerX + std::cos(angle) * rayInnerRadius;
        auto innerY = centerY + std::sin(angle) * rayInnerRadius;
        auto outerX = centerX + std::cos(angle) * rayOuterRadius;
        auto outerY = centerY + std::sin(angle) * rayOuterRadius;

        g.drawLine(innerX, innerY, outerX, outerY, stroke * 1.2f);
    }

    // Additional shorter rays between main rays
    auto shortRayInnerRadius = sunRadius * 1.3f;
    auto shortRayOuterRadius = sunRadius * 1.7f;

    for (int i = 0; i < rayCount; ++i)
    {
        auto angle = ((i + 0.5f) / static_cast<float>(rayCount)) * juce::MathConstants<float>::twoPi;
        auto innerX = centerX + std::cos(angle) * shortRayInnerRadius;
        auto innerY = centerY + std::sin(angle) * shortRayInnerRadius;
        auto outerX = centerX + std::cos(angle) * shortRayOuterRadius;
        auto outerY = centerY + std::sin(angle) * shortRayOuterRadius;

        g.drawLine(innerX, innerY, outerX, outerY, stroke * 0.8f);
    }
}

void FancyIconPack::drawThemeDark(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Moon and stars icon for dark theme
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto moonRadius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.25f;

    // Crescent moon
    auto moonCenterX = centerX - moonRadius * 0.3f;
    auto moonCenterY = centerY;

    // Outer moon circle
    g.setColour(color);
    g.fillEllipse(moonCenterX - moonRadius, moonCenterY - moonRadius, moonRadius * 2, moonRadius * 2);

    // Create crescent shape manually using path
    auto cutoutRadius = moonRadius * 0.8f;
    auto cutoutCenterX = moonCenterX + moonRadius * 0.4f;

    g.setColour(color);
    juce::Path crescentPath;

    // Create crescent shape manually
    auto crescentPoints = 12;

    // Start with outer arc (left side of moon)
    for (int i = 0; i <= crescentPoints; ++i)
    {
        auto angle = juce::MathConstants<float>::pi * 0.5f + (i / static_cast<float>(crescentPoints)) * juce::MathConstants<float>::pi;
        auto x = moonCenterX + std::cos(angle) * moonRadius;
        auto y = moonCenterY + std::sin(angle) * moonRadius;

        if (i == 0)
            crescentPath.startNewSubPath(x, y);
        else
            crescentPath.lineTo(x, y);
    }

    // Inner crescent curve (right side cutout)
    for (int i = crescentPoints; i >= 0; --i)
    {
        auto angle = juce::MathConstants<float>::pi * 0.5f + (i / static_cast<float>(crescentPoints)) * juce::MathConstants<float>::pi;
        auto x = cutoutCenterX + std::cos(angle) * cutoutRadius * 0.7f;
        auto y = moonCenterY + std::sin(angle) * cutoutRadius * 0.7f;
        crescentPath.lineTo(x, y);
    }

    crescentPath.closeSubPath();
    g.fillPath(crescentPath);

    // Stars around the moon
    juce::Array<juce::Point<float>> starPositions = {
        juce::Point<float>(centerX + moonRadius * 1.2f, centerY - moonRadius * 0.8f),
        juce::Point<float>(centerX + moonRadius * 0.8f, centerY + moonRadius * 1.1f),
        juce::Point<float>(centerX - moonRadius * 1.3f, centerY - moonRadius * 1.2f),
        juce::Point<float>(centerX + moonRadius * 1.5f, centerY + moonRadius * 0.3f)
    };

    auto starSizes = {0.8f, 0.6f, 0.5f, 0.7f};
    auto sizeIt = starSizes.begin();

    for (auto& starPos : starPositions)
    {
        auto starSize = stroke * (*sizeIt) * 2;

        // Simple 4-pointed star
        g.drawLine(starPos.x - starSize, starPos.y, starPos.x + starSize, starPos.y, stroke * 0.8f);
        g.drawLine(starPos.x, starPos.y - starSize, starPos.x, starPos.y + starSize, stroke * 0.8f);

        // Center dot
        auto dotRadius = stroke * 0.5f;
        g.fillEllipse(starPos.x - dotRadius, starPos.y - dotRadius, dotRadius * 2, dotRadius * 2);

        ++sizeIt;
    }
}

void FancyIconPack::drawColorPicker(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Color picker palette with paintbrush
    auto paletteArea = iconBounds.removeFromLeft(iconBounds.getWidth() * 0.6f);
    auto brushArea = iconBounds; // remaining area for brush

    // Color palette (artist's palette shape)
    juce::Path palette;
    auto paletteWidth = paletteArea.getWidth();
    auto paletteHeight = paletteArea.getHeight() * 0.7f;
    auto paletteX = paletteArea.getX();
    auto paletteY = paletteArea.getCentreY() - paletteHeight * 0.5f;

    // Palette outline (irregular oval with thumb hole)
    palette.startNewSubPath(paletteX, paletteY + paletteHeight * 0.5f);
    palette.quadraticTo(paletteX, paletteY, paletteX + paletteWidth * 0.3f, paletteY);
    palette.quadraticTo(paletteX + paletteWidth * 0.8f, paletteY, paletteX + paletteWidth, paletteY + paletteHeight * 0.3f);
    palette.quadraticTo(paletteX + paletteWidth, paletteY + paletteHeight * 0.7f, paletteX + paletteWidth * 0.7f, paletteY + paletteHeight);
    palette.quadraticTo(paletteX + paletteWidth * 0.3f, paletteY + paletteHeight, paletteX, paletteY + paletteHeight * 0.5f);

    g.setColour(color);
    g.strokePath(palette, createStroke(stroke));

    // Color dabs on palette
    juce::Array<juce::Colour> paletteColors = {
        juce::Colours::red.withAlpha(0.7f),
        juce::Colours::blue.withAlpha(0.7f),
        juce::Colours::yellow.withAlpha(0.7f),
        juce::Colours::green.withAlpha(0.7f),
        juce::Colours::purple.withAlpha(0.7f),
        juce::Colours::orange.withAlpha(0.7f)
    };

    juce::Array<juce::Point<float>> dabPositions = {
        juce::Point<float>(paletteX + paletteWidth * 0.2f, paletteY + paletteHeight * 0.3f),
        juce::Point<float>(paletteX + paletteWidth * 0.5f, paletteY + paletteHeight * 0.2f),
        juce::Point<float>(paletteX + paletteWidth * 0.7f, paletteY + paletteHeight * 0.4f),
        juce::Point<float>(paletteX + paletteWidth * 0.3f, paletteY + paletteHeight * 0.6f),
        juce::Point<float>(paletteX + paletteWidth * 0.6f, paletteY + paletteHeight * 0.7f),
        juce::Point<float>(paletteX + paletteWidth * 0.8f, paletteY + paletteHeight * 0.6f)
    };

    auto dabRadius = stroke * 2;
    for (int i = 0; i < paletteColors.size() && i < dabPositions.size(); ++i)
    {
        auto dabColor = paletteColors[i];
        auto dabPos = dabPositions[i];

        g.setColour(dabColor);
        g.fillEllipse(dabPos.x - dabRadius, dabPos.y - dabRadius, dabRadius * 2, dabRadius * 2);

        // Small highlight
        g.setColour(dabColor.brighter(0.3f));
        auto highlightRadius = dabRadius * 0.4f;
        g.fillEllipse(dabPos.x - highlightRadius, dabPos.y - dabRadius * 0.3f, highlightRadius * 2, highlightRadius * 2);
    }

    // Paintbrush
    auto brushCenterX = brushArea.getCentreX();
    auto brushCenterY = brushArea.getCentreY();
    auto brushLength = juce::jmin(brushArea.getHeight() * 0.6f, brushArea.getWidth() * 0.8f); // Ensure it fits
    auto brushAngle = -0.2f; // Reduced angle to keep within bounds

    // Brush handle
    auto handleLength = brushLength * 0.5f;
    auto handleStart = juce::Point<float>(brushCenterX - std::cos(brushAngle) * handleLength * 0.5f,
                                        brushCenterY + std::sin(brushAngle) * handleLength * 0.5f);
    auto handleEnd = juce::Point<float>(brushCenterX + std::cos(brushAngle) * handleLength * 0.5f,
                                      brushCenterY - std::sin(brushAngle) * handleLength * 0.5f);

    // Ensure handle stays within brush area bounds
    handleStart.x = juce::jlimit(brushArea.getX(), brushArea.getRight(), handleStart.x);
    handleStart.y = juce::jlimit(brushArea.getY(), brushArea.getBottom(), handleStart.y);
    handleEnd.x = juce::jlimit(brushArea.getX(), brushArea.getRight(), handleEnd.x);
    handleEnd.y = juce::jlimit(brushArea.getY(), brushArea.getBottom(), handleEnd.y);

    g.setColour(color);
    g.drawLine(handleStart.x, handleStart.y, handleEnd.x, handleEnd.y, stroke * 1.5f);

    // Brush ferrule (metal band)
    auto ferruleOffset = stroke * 1.5f; // Reduced offset
    auto ferruleCenter = handleEnd + juce::Point<float>(std::cos(brushAngle) * ferruleOffset, -std::sin(brushAngle) * ferruleOffset);

    // Ensure ferrule stays within bounds
    ferruleCenter.x = juce::jlimit(brushArea.getX() + stroke, brushArea.getRight() - stroke, ferruleCenter.x);
    ferruleCenter.y = juce::jlimit(brushArea.getY() + stroke, brushArea.getBottom() - stroke, ferruleCenter.y);

    auto ferruleSize = stroke * 2.5f; // Slightly smaller
    g.setColour(color.withAlpha(0.8f));
    g.fillEllipse(ferruleCenter.x - ferruleSize * 0.5f, ferruleCenter.y - ferruleSize * 0.3f, ferruleSize, ferruleSize * 0.6f);

    // Brush bristles - ensure they stay within bounds
    auto bristleOffset = stroke * 1.2f; // Reduced offset
    auto bristleStart = ferruleCenter + juce::Point<float>(std::cos(brushAngle) * bristleOffset, -std::sin(brushAngle) * bristleOffset);
    auto bristleLength = stroke * 2.5f; // Reduced length
    auto bristleEnd = bristleStart + juce::Point<float>(std::cos(brushAngle) * bristleLength, -std::sin(brushAngle) * bristleLength);

    // Clamp bristle positions to brush area
    bristleStart.x = juce::jlimit(brushArea.getX(), brushArea.getRight(), bristleStart.x);
    bristleStart.y = juce::jlimit(brushArea.getY(), brushArea.getBottom(), bristleStart.y);
    bristleEnd.x = juce::jlimit(brushArea.getX(), brushArea.getRight(), bristleEnd.x);
    bristleEnd.y = juce::jlimit(brushArea.getY(), brushArea.getBottom(), bristleEnd.y);

    g.setColour(color);
    // Multiple bristle lines for brush effect
    for (int i = -1; i <= 1; ++i) // Reduced bristle count
    {
        auto offset = juce::Point<float>(-std::sin(brushAngle) * i * stroke * 0.2f, -std::cos(brushAngle) * i * stroke * 0.2f);
        auto bristleStartWithOffset = bristleStart + offset;
        auto bristleEndWithOffset = bristleEnd + offset;

        // Ensure offset bristles stay within bounds
        bristleStartWithOffset.x = juce::jlimit(brushArea.getX(), brushArea.getRight(), bristleStartWithOffset.x);
        bristleStartWithOffset.y = juce::jlimit(brushArea.getY(), brushArea.getBottom(), bristleStartWithOffset.y);
        bristleEndWithOffset.x = juce::jlimit(brushArea.getX(), brushArea.getRight(), bristleEndWithOffset.x);
        bristleEndWithOffset.y = juce::jlimit(brushArea.getY(), brushArea.getBottom(), bristleEndWithOffset.y);

        g.drawLine(bristleStartWithOffset.x, bristleStartWithOffset.y, bristleEndWithOffset.x, bristleEndWithOffset.y, stroke * 0.6f);
    }

    // Paint on brush tip - ensure it stays within bounds
    g.setColour(juce::Colours::red.withAlpha(0.6f));
    auto paintRadius = stroke * 1.0f; // Slightly smaller
    auto paintX = juce::jlimit(brushArea.getX() + paintRadius, brushArea.getRight() - paintRadius, bristleEnd.x);
    auto paintY = juce::jlimit(brushArea.getY() + paintRadius, brushArea.getBottom() - paintRadius, bristleEnd.y);
    g.fillEllipse(paintX - paintRadius, paintY - paintRadius, paintRadius * 2, paintRadius * 2);
}

// Preset Management
// ============================================================================

void FancyIconPack::drawPresetBrowser(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Library/browser window with folder structure
    g.setColour(color);
    g.drawRoundedRectangle(iconBounds, stroke, stroke);

    // Title bar
    auto titleBarHeight = iconBounds.getHeight() * 0.15f;
    auto titleBar = iconBounds.removeFromTop(titleBarHeight);
    g.fillRoundedRectangle(titleBar, stroke);

    // Browser content area
    auto contentArea = iconBounds.reduced(stroke);

    // Folder tree structure (left side)
    auto treeWidth = contentArea.getWidth() * 0.4f;
    auto treeArea = contentArea.removeFromLeft(treeWidth);

    g.setColour(color.withAlpha(0.3f));
    g.drawLine(treeArea.getRight(), treeArea.getY(), treeArea.getRight(), treeArea.getBottom(), stroke * 0.5f);

    // Folder icons and names
    g.setColour(color.withAlpha(0.7f));
    auto folderHeight = treeArea.getHeight() / 5.0f;

    for (int i = 0; i < 4; ++i)
    {
        auto folderY = treeArea.getY() + folderHeight * i;
        auto indent = (i % 2) * stroke * 2; // Indentation for hierarchy

        // Folder icon
        auto folderIconSize = stroke * 2;
        auto folderX = treeArea.getX() + indent;
        g.fillRoundedRectangle(folderX, folderY + folderHeight * 0.3f,
                              folderIconSize, folderIconSize * 0.7f, stroke * 0.3f);

        // Folder name line
        auto nameX = folderX + folderIconSize + stroke;
        auto nameWidth = treeArea.getRight() - nameX - stroke;
        g.drawLine(nameX, folderY + folderHeight * 0.5f,
                  nameX + nameWidth * (0.7f - i * 0.1f), folderY + folderHeight * 0.5f, stroke * 0.6f);
    }

    // Preset list (right side)
    auto listArea = contentArea.reduced(stroke);
    g.setColour(color.withAlpha(0.6f));

    auto presetCount = 6;
    auto presetHeight = listArea.getHeight() / presetCount;

    for (int i = 0; i < presetCount; ++i)
    {
        auto presetY = listArea.getY() + presetHeight * i;

        // Highlight selected preset
        if (i == 2)
        {
            g.setColour(color.brighter(0.3f));
            g.fillRoundedRectangle(listArea.getX(), presetY, listArea.getWidth(), presetHeight * 0.8f, stroke * 0.5f);
            g.setColour(color.darker(0.2f));
        }

        // Preset name
        auto presetNameWidth = listArea.getWidth() * (0.8f - i * 0.05f);
        g.drawLine(listArea.getX() + stroke, presetY + presetHeight * 0.4f,
                  listArea.getX() + presetNameWidth, presetY + presetHeight * 0.4f, stroke * 0.7f);

        if (i == 2)
            g.setColour(color.withAlpha(0.6f));
    }

    // Search/filter icon in top right
    g.setColour(color.brighter(0.2f));
    auto searchSize = stroke * 2;
    auto searchX = iconBounds.getRight() - searchSize - stroke * 2;
    auto searchY = titleBar.getCentreY() - searchSize * 0.5f;

    // Magnifying glass
    g.drawEllipse(searchX, searchY, searchSize, searchSize, stroke * 0.6f);
    auto handleX = searchX + searchSize * 0.8f;
    auto handleY = searchY + searchSize * 0.8f;
    g.drawLine(handleX, handleY, handleX + stroke, handleY + stroke, stroke * 0.8f);
}

void FancyIconPack::drawPresetFavorite(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Star icon for favorites
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto outerRadius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.4f;
    auto innerRadius = outerRadius * 0.4f;

    juce::Path star;
    auto points = 5;
    auto angleStep = juce::MathConstants<float>::twoPi / (points * 2);

    for (int i = 0; i < points * 2; ++i)
    {
        auto angle = i * angleStep - juce::MathConstants<float>::halfPi;
        auto radius = (i % 2 == 0) ? outerRadius : innerRadius;
        auto x = centerX + std::cos(angle) * radius;
        auto y = centerY + std::sin(angle) * radius;

        if (i == 0)
            star.startNewSubPath(x, y);
        else
            star.lineTo(x, y);
    }
    star.closeSubPath();

    g.setColour(color);
    g.fillPath(star);
    g.strokePath(star, createStroke(stroke));

    // Optional glow/highlight effect
    g.setColour(color.brighter(0.3f).withAlpha(0.5f));
    auto glowStar = star;
    glowStar.applyTransform(juce::AffineTransform::scale(1.1f, 1.1f, centerX, centerY));
    g.strokePath(glowStar, createStroke(stroke * 0.5f));

    // Small sparkle effects around the star
    g.setColour(color.brighter(0.4f));
    juce::Array<juce::Point<float>> sparklePositions = {
        juce::Point<float>(centerX + outerRadius * 0.8f, centerY - outerRadius * 0.6f),
        juce::Point<float>(centerX - outerRadius * 0.7f, centerY + outerRadius * 0.8f),
        juce::Point<float>(centerX + outerRadius * 0.6f, centerY + outerRadius * 0.9f),
        juce::Point<float>(centerX - outerRadius * 0.9f, centerY - outerRadius * 0.5f)
    };

    for (auto& pos : sparklePositions)
    {
        auto sparkleSize = stroke * 0.8f;
        // Small cross sparkle
        g.drawLine(pos.x - sparkleSize, pos.y, pos.x + sparkleSize, pos.y, stroke * 0.6f);
        g.drawLine(pos.x, pos.y - sparkleSize, pos.x, pos.y + sparkleSize, stroke * 0.6f);
    }
}

void FancyIconPack::drawPresetRandom(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Dice icon for random preset selection
    auto diceSize = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.7f;
    auto diceX = iconBounds.getCentreX() - diceSize * 0.5f;
    auto diceY = iconBounds.getCentreY() - diceSize * 0.5f;

    g.setColour(color);

    // Main die face
    g.fillRoundedRectangle(diceX, diceY, diceSize, diceSize, stroke);
    g.drawRoundedRectangle(diceX, diceY, diceSize, diceSize, stroke, stroke * 0.8f);

    // 3D effect - right face
    auto faceOffset = stroke * 2;
    juce::Path rightFace;
    rightFace.startNewSubPath(diceX + diceSize, diceY);
    rightFace.lineTo(diceX + diceSize + faceOffset, diceY - faceOffset);
    rightFace.lineTo(diceX + diceSize + faceOffset, diceY + diceSize - faceOffset);
    rightFace.lineTo(diceX + diceSize, diceY + diceSize);
    rightFace.closeSubPath();

    g.setColour(color.darker(0.3f));
    g.fillPath(rightFace);
    g.strokePath(rightFace, createStroke(stroke * 0.6f));

    // 3D effect - top face
    juce::Path topFace;
    topFace.startNewSubPath(diceX, diceY);
    topFace.lineTo(diceX + faceOffset, diceY - faceOffset);
    topFace.lineTo(diceX + diceSize + faceOffset, diceY - faceOffset);
    topFace.lineTo(diceX + diceSize, diceY);
    topFace.closeSubPath();

    g.setColour(color.brighter(0.2f));
    g.fillPath(topFace);
    g.strokePath(topFace, createStroke(stroke * 0.6f));

    // Dice dots (show number 5)
    auto dotRadius = stroke * 0.7f;
    auto dotSpacing = diceSize * 0.25f;
    auto centerDotX = diceX + diceSize * 0.5f;
    auto centerDotY = diceY + diceSize * 0.5f;

    g.setColour(color.contrasting(0.8f));

    // Five dots arrangement
    juce::Array<juce::Point<float>> dotPositions = {
        juce::Point<float>(diceX + dotSpacing, diceY + dotSpacing), // Top-left
        juce::Point<float>(diceX + diceSize - dotSpacing, diceY + dotSpacing), // Top-right
        juce::Point<float>(centerDotX, centerDotY), // Center
        juce::Point<float>(diceX + dotSpacing, diceY + diceSize - dotSpacing), // Bottom-left
        juce::Point<float>(diceX + diceSize - dotSpacing, diceY + diceSize - dotSpacing) // Bottom-right
    };

    for (auto& pos : dotPositions)
    {
        g.fillEllipse(pos.x - dotRadius, pos.y - dotRadius, dotRadius * 2, dotRadius * 2);
    }

    // Motion lines to indicate randomness/rolling
    g.setColour(color.withAlpha(0.6f));
    auto motionLineCount = 3;
    for (int i = 0; i < motionLineCount; ++i)
    {
        auto lineLength = stroke * (2 + i);
        auto lineY = diceY - stroke * (2 + i * 1.5f);
        auto lineStartX = diceX + diceSize * 0.7f + i * stroke;

        g.drawLine(lineStartX, lineY, lineStartX + lineLength, lineY, stroke * 0.5f);
    }
}

void FancyIconPack::drawInitPreset(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Initialize/Reset symbol with refresh arrows and "INIT" indication
    auto centerX = iconBounds.getCentreX();
    auto centerY = iconBounds.getCentreY();
    auto radius = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.35f;

    g.setColour(color);

    // Circular refresh arrows
    auto arrowWidth = stroke * 2;
    auto arrowLength = stroke * 3;

    // First arrow (clockwise, top-right)
    juce::Path arrow1;
    auto startAngle1 = juce::MathConstants<float>::pi * 0.1f;
    auto endAngle1 = juce::MathConstants<float>::pi * 0.9f;

    for (float angle = startAngle1; angle <= endAngle1; angle += 0.1f)
    {
        auto x = centerX + std::cos(angle) * radius;
        auto y = centerY + std::sin(angle) * radius;

        if (angle == startAngle1)
            arrow1.startNewSubPath(x, y);
        else
            arrow1.lineTo(x, y);
    }

    g.strokePath(arrow1, createStroke(stroke * 1.2f));

    // Arrow head for first arrow
    auto headX1 = centerX + std::cos(endAngle1) * radius;
    auto headY1 = centerY + std::sin(endAngle1) * radius;
    auto headAngle1 = endAngle1 + juce::MathConstants<float>::halfPi;

    juce::Path arrowHead1;
    arrowHead1.startNewSubPath(headX1, headY1);
    arrowHead1.lineTo(headX1 - std::cos(headAngle1 - 0.3f) * arrowLength,
                     headY1 - std::sin(headAngle1 - 0.3f) * arrowLength);
    arrowHead1.lineTo(headX1 - std::cos(headAngle1 + 0.3f) * arrowLength,
                     headY1 - std::sin(headAngle1 + 0.3f) * arrowLength);
    arrowHead1.closeSubPath();

    g.fillPath(arrowHead1);

    // Second arrow (counter-clockwise, bottom-left)
    juce::Path arrow2;
    auto startAngle2 = juce::MathConstants<float>::pi * 1.1f;
    auto endAngle2 = juce::MathConstants<float>::pi * 1.9f;

    for (float angle = startAngle2; angle <= endAngle2; angle += 0.1f)
    {
        auto x = centerX + std::cos(angle) * radius;
        auto y = centerY + std::sin(angle) * radius;

        if (angle == startAngle2)
            arrow2.startNewSubPath(x, y);
        else
            arrow2.lineTo(x, y);
    }

    g.strokePath(arrow2, createStroke(stroke * 1.2f));

    // Arrow head for second arrow
    auto headX2 = centerX + std::cos(endAngle2) * radius;
    auto headY2 = centerY + std::sin(endAngle2) * radius;
    auto headAngle2 = endAngle2 - juce::MathConstants<float>::halfPi;

    juce::Path arrowHead2;
    arrowHead2.startNewSubPath(headX2, headY2);
    arrowHead2.lineTo(headX2 - std::cos(headAngle2 - 0.3f) * arrowLength,
                     headY2 - std::sin(headAngle2 - 0.3f) * arrowLength);
    arrowHead2.lineTo(headX2 - std::cos(headAngle2 + 0.3f) * arrowLength,
                     headY2 - std::sin(headAngle2 + 0.3f) * arrowLength);
    arrowHead2.closeSubPath();

    g.fillPath(arrowHead2);

    // Center "INIT" or reset symbol
    g.setColour(color.withAlpha(0.8f));
    auto symbolSize = radius * 0.6f;

    // Simple geometric reset symbol (square with diagonal)
    auto symbolBounds = juce::Rectangle<float>(centerX - symbolSize * 0.5f, centerY - symbolSize * 0.5f,
                                             symbolSize, symbolSize);

    g.drawRoundedRectangle(symbolBounds, stroke * 0.5f, stroke * 0.8f);

    // Diagonal lines forming an "X" or reset cross
    g.drawLine(symbolBounds.getX(), symbolBounds.getY(),
              symbolBounds.getRight(), symbolBounds.getBottom(), stroke * 0.8f);
    g.drawLine(symbolBounds.getRight(), symbolBounds.getY(),
              symbolBounds.getX(), symbolBounds.getBottom(), stroke * 0.8f);

    // Optional: Factory reset indicator dots
    g.setColour(color.brighter(0.3f));
    auto dotRadius = stroke * 0.4f;
    auto dotDistance = radius * 1.3f;

    for (int i = 0; i < 4; ++i)
    {
        auto angle = (i / 4.0f) * juce::MathConstants<float>::twoPi;
        auto dotX = centerX + std::cos(angle) * dotDistance;
        auto dotY = centerY + std::sin(angle) * dotDistance;
        g.fillEllipse(dotX - dotRadius, dotY - dotRadius, dotRadius * 2, dotRadius * 2);
    }
}

void FancyIconPack::drawSavePreset(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Floppy disk save icon (classic save symbol)
    auto diskSize = juce::jmin(iconBounds.getWidth(), iconBounds.getHeight()) * 0.8f;
    auto diskX = iconBounds.getCentreX() - diskSize * 0.5f;
    auto diskY = iconBounds.getCentreY() - diskSize * 0.5f;

    g.setColour(color);

    // Main disk body
    g.fillRoundedRectangle(diskX, diskY, diskSize, diskSize, stroke);
    g.drawRoundedRectangle(diskX, diskY, diskSize, diskSize, stroke, stroke * 0.8f);

    // Metal shutter (top part)
    auto shutterHeight = diskSize * 0.15f;
    auto shutterY = diskY + shutterHeight * 0.5f;
    g.setColour(color.darker(0.3f));
    g.fillRoundedRectangle(diskX + stroke, shutterY, diskSize - stroke * 2, shutterHeight,
                          stroke * 0.3f);

    // Shutter opening
    auto openingWidth = diskSize * 0.6f;
    auto openingX = diskX + (diskSize - openingWidth) * 0.5f;
    g.setColour(color.darker(0.6f));
    g.fillRoundedRectangle(openingX, shutterY + stroke * 0.5f, openingWidth, shutterHeight - stroke,
                          stroke * 0.2f);

    // Write protect tab
    g.setColour(color.brighter(0.2f));
    auto tabSize = stroke * 2;
    auto tabX = diskX + diskSize - tabSize - stroke;
    auto tabY = diskY + diskSize * 0.3f;
    g.fillRoundedRectangle(tabX, tabY, tabSize, tabSize * 0.6f, stroke * 0.3f);

    // Label area
    g.setColour(color.withAlpha(0.7f));
    auto labelHeight = diskSize * 0.4f;
    auto labelY = diskY + diskSize * 0.5f;
    auto labelMargin = stroke * 2;

    // Label lines (simulating text)
    auto lineCount = 3;
    auto lineSpacing = labelHeight / (lineCount + 1);

    for (int i = 0; i < lineCount; ++i)
    {
        auto lineY = labelY + lineSpacing * (i + 1);
        auto lineWidth = (diskSize - labelMargin * 2) * (0.9f - i * 0.2f);
        g.drawLine(diskX + labelMargin, lineY,
                  diskX + labelMargin + lineWidth, lineY, stroke * 0.6f);
    }

    // Corner notch (characteristic floppy disk feature)
    g.setColour(color.darker(0.4f));
    auto notchSize = stroke * 1.5f;
    juce::Path notch;
    notch.startNewSubPath(diskX + diskSize - notchSize, diskY);
    notch.lineTo(diskX + diskSize, diskY);
    notch.lineTo(diskX + diskSize, diskY + notchSize);
    notch.closeSubPath();
    g.fillPath(notch);

    // Save indicator arrow (pointing down)
    g.setColour(color.brighter(0.4f));
    auto arrowSize = stroke * 1.5f;
    auto arrowX = diskX + diskSize * 0.8f;
    auto arrowY = diskY - stroke * 2;

    juce::Path saveArrow;
    saveArrow.startNewSubPath(arrowX, arrowY);
    saveArrow.lineTo(arrowX + arrowSize, arrowY - arrowSize);
    saveArrow.lineTo(arrowX - arrowSize, arrowY - arrowSize);
    saveArrow.closeSubPath();

    g.fillPath(saveArrow);

    // Vertical line for arrow shaft
    g.drawLine(arrowX, arrowY, arrowX, arrowY - arrowSize * 2, stroke * 0.8f);
}

void FancyIconPack::drawLockParameter(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Padlock icon for parameter locking
    auto lockHeight = iconBounds.getHeight() * 0.8f;
    auto lockWidth = iconBounds.getWidth() * 0.6f;
    auto lockX = iconBounds.getCentreX() - lockWidth * 0.5f;
    auto lockY = iconBounds.getCentreY() - lockHeight * 0.5f;

    // Lock body (bottom part)
    auto bodyHeight = lockHeight * 0.6f;
    auto bodyY = lockY + lockHeight - bodyHeight;

    g.setColour(color);
    g.fillRoundedRectangle(lockX, bodyY, lockWidth, bodyHeight, stroke);
    g.drawRoundedRectangle(lockX, bodyY, lockWidth, bodyHeight, stroke, stroke * 0.8f);

    // Lock shackle (top curved part)
    auto shackleWidth = lockWidth * 0.6f;
    auto shackleHeight = lockHeight * 0.5f;
    auto shackleX = lockX + (lockWidth - shackleWidth) * 0.5f;
    auto shackleY = lockY;
    auto shackleThickness = stroke * 1.5f;

    // Create shackle using path to make it hollow
    juce::Path shacklePath;
    auto shackleRadius = shackleWidth * 0.5f;

    // Outer path
    juce::Path outerShackle;
    outerShackle.addRoundedRectangle(shackleX, shackleY, shackleWidth, shackleHeight * 1.2f, shackleRadius);

    // Inner path (cutout)
    auto innerShackleWidth = shackleWidth - shackleThickness * 2;
    auto innerShackleHeight = shackleHeight * 0.8f;
    auto innerShackleX = shackleX + shackleThickness;
    auto innerShackleY = shackleY + shackleThickness;
    auto innerRadius = innerShackleWidth * 0.5f;

    juce::Path innerShackle;
    innerShackle.addRoundedRectangle(innerShackleX, innerShackleY, innerShackleWidth, innerShackleHeight, innerRadius);

    // Subtract inner from outer to create hollow effect
    shacklePath = outerShackle;
    shacklePath.setUsingNonZeroWinding(false);
    shacklePath.addPath(innerShackle);

    g.setColour(color);
    g.fillPath(shacklePath);

    // Keyhole in lock body
    g.setColour(color.contrasting(0.8f));
    auto keyholeRadius = stroke * 1.2f;
    auto keyholeX = lockX + lockWidth * 0.5f;
    auto keyholeY = bodyY + bodyHeight * 0.4f;

    // Circular part of keyhole
    g.fillEllipse(keyholeX - keyholeRadius, keyholeY - keyholeRadius,
                  keyholeRadius * 2, keyholeRadius * 2);

    // Rectangular slot part of keyhole
    auto slotWidth = stroke * 0.6f;
    auto slotHeight = bodyHeight * 0.3f;
    g.fillRoundedRectangle(keyholeX - slotWidth * 0.5f, keyholeY,
                          slotWidth, slotHeight, stroke * 0.2f);

    // Lock status indicator (closed/locked)
    g.setColour(color.brighter(0.3f));
    auto indicatorRadius = stroke * 0.5f;
    auto indicatorX = lockX + lockWidth - stroke * 2;
    auto indicatorY = lockY + stroke;
    g.fillEllipse(indicatorX - indicatorRadius, indicatorY - indicatorRadius,
                  indicatorRadius * 2, indicatorRadius * 2);

    // Parameter symbol (small knob or slider behind/next to lock)
    g.setColour(color.withAlpha(0.4f));
    auto paramRadius = stroke * 2;
    auto paramX = iconBounds.getRight() - paramRadius - stroke;
    auto paramY = iconBounds.getBottom() - paramRadius - stroke;

    g.drawEllipse(paramX - paramRadius, paramY - paramRadius,
                  paramRadius * 2, paramRadius * 2, stroke * 0.6f);

    // Parameter value indicator line
    g.drawLine(paramX, paramY - paramRadius * 0.6f, paramX, paramY - paramRadius * 0.3f, stroke * 0.5f);
}

void FancyIconPack::drawParameterAutomation(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Automation curve with nodes and timeline
    g.setColour(color);

    // Timeline base
    auto timelineY = iconBounds.getBottom() - stroke * 2;
    g.drawLine(iconBounds.getX(), timelineY, iconBounds.getRight(), timelineY, stroke * 0.5f);

    // Automation curve path
    juce::Path automationCurve;
    auto curveHeight = iconBounds.getHeight() * 0.6f;
    auto curveTop = iconBounds.getY() + iconBounds.getHeight() * 0.1f;

    // Define automation points (time, value)
    juce::Array<juce::Point<float>> automationPoints = {
        juce::Point<float>(0.1f, 0.2f),
        juce::Point<float>(0.3f, 0.8f),
        juce::Point<float>(0.6f, 0.4f),
        juce::Point<float>(0.9f, 0.9f)
    };

    // Draw smooth curve through points
    for (int i = 0; i < automationPoints.size(); ++i)
    {
        auto& point = automationPoints[i];
        auto x = iconBounds.getX() + point.x * iconBounds.getWidth();
        auto y = curveTop + (1.0f - point.y) * curveHeight;

        if (i == 0)
            automationCurve.startNewSubPath(x, y);
        else
        {
            // Create smooth curves between points
            auto& prevPoint = automationPoints[i - 1];
            auto prevX = iconBounds.getX() + prevPoint.x * iconBounds.getWidth();
            auto prevY = curveTop + (1.0f - prevPoint.y) * curveHeight;

            auto controlOffset = (x - prevX) * 0.3f;
            automationCurve.cubicTo(prevX + controlOffset, prevY,
                                   x - controlOffset, y,
                                   x, y);
        }
    }

    g.strokePath(automationCurve, createStroke(stroke * 1.2f));

    // Automation nodes
    g.setColour(color.brighter(0.3f));
    auto nodeRadius = stroke * 1.2f;

    for (auto& point : automationPoints)
    {
        auto x = iconBounds.getX() + point.x * iconBounds.getWidth();
        auto y = curveTop + (1.0f - point.y) * curveHeight;

        g.fillEllipse(x - nodeRadius, y - nodeRadius, nodeRadius * 2, nodeRadius * 2);
        g.setColour(color.darker(0.2f));
        g.drawEllipse(x - nodeRadius, y - nodeRadius, nodeRadius * 2, nodeRadius * 2, stroke * 0.6f);
        g.setColour(color.brighter(0.3f));
    }

    // Time markers on timeline
    g.setColour(color.withAlpha(0.6f));
    auto markerCount = 4;
    for (int i = 1; i <= markerCount; ++i)
    {
        auto markerX = iconBounds.getX() + (iconBounds.getWidth() / (markerCount + 1)) * i;
        g.drawLine(markerX, timelineY - stroke, markerX, timelineY + stroke, stroke * 0.5f);
    }

    // Automation indicator symbol (A or AUTO)
    g.setColour(color.brighter(0.4f));
    auto symbolSize = stroke * 1.5f;
    auto symbolX = iconBounds.getX() + stroke;
    auto symbolY = iconBounds.getY() + stroke;

    // Simple "A" for automation
    juce::Path autoSymbol;
    autoSymbol.startNewSubPath(symbolX, symbolY + symbolSize * 2);
    autoSymbol.lineTo(symbolX + symbolSize, symbolY);
    autoSymbol.lineTo(symbolX + symbolSize * 2, symbolY + symbolSize * 2);

    // Crossbar for "A"
    autoSymbol.startNewSubPath(symbolX + symbolSize * 0.3f, symbolY + symbolSize * 1.3f);
    autoSymbol.lineTo(symbolX + symbolSize * 1.7f, symbolY + symbolSize * 1.3f);

    g.strokePath(autoSymbol, createStroke(stroke * 0.8f));

    // Recording/active indicator
    g.setColour(juce::Colours::red.withAlpha(0.8f));
    auto recordRadius = stroke * 0.6f;
    auto recordX = iconBounds.getRight() - stroke * 3;
    auto recordY = iconBounds.getY() + stroke * 2;
    g.fillEllipse(recordX - recordRadius, recordY - recordRadius, recordRadius * 2, recordRadius * 2);
}

// Interaction Features
// ============================================================================

void FancyIconPack::drawDragToAssign(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Drag gesture: source object moving to target with assignment indication
    auto sourceSize = iconBounds.getWidth() * 0.25f;
    auto targetSize = iconBounds.getWidth() * 0.3f;

    // Source object (parameter/control being dragged)
    auto sourceX = iconBounds.getX() + sourceSize * 0.5f;
    auto sourceY = iconBounds.getY() + sourceSize * 0.5f;

    g.setColour(color.brighter(0.3f));
    g.fillRoundedRectangle(sourceX - sourceSize * 0.5f, sourceY - sourceSize * 0.5f,
                          sourceSize, sourceSize, stroke);
    g.setColour(color);
    g.drawRoundedRectangle(sourceX - sourceSize * 0.5f, sourceY - sourceSize * 0.5f,
                          sourceSize, sourceSize, stroke, stroke * 0.8f);

    // Target destination
    auto targetX = iconBounds.getRight() - targetSize * 0.5f;
    auto targetY = iconBounds.getBottom() - targetSize * 0.5f;

    g.setColour(color.withAlpha(0.7f));
    g.drawRoundedRectangle(targetX - targetSize * 0.5f, targetY - targetSize * 0.5f,
                          targetSize, targetSize, stroke * 1.5f, stroke);

    // Dashed outline for target to show it's a drop zone
    g.setColour(color.brighter(0.2f));
    auto dashLength = stroke * 2;
    auto targetBounds = juce::Rectangle<float>(targetX - targetSize * 0.5f, targetY - targetSize * 0.5f,
                                             targetSize, targetSize);

    // Draw dashed border manually
    auto perimeterLength = (targetBounds.getWidth() + targetBounds.getHeight()) * 2;
    auto dashCount = static_cast<int>(perimeterLength / (dashLength * 2));

    for (int i = 0; i < dashCount; ++i)
    {
        auto t = (i * 2.0f * dashLength) / perimeterLength;
        if (t > 1.0f) break;

        juce::Point<float> startPoint, endPoint;
        auto dashT = (dashLength) / perimeterLength;

        // Calculate positions along rectangle perimeter
        if (t < 0.25f) // Top edge
        {
            auto edgeT = t * 4;
            startPoint = juce::Point<float>(targetBounds.getX() + edgeT * targetBounds.getWidth(), targetBounds.getY());
            endPoint = juce::Point<float>(targetBounds.getX() + juce::jmin(1.0f, edgeT + dashT) * targetBounds.getWidth(), targetBounds.getY());
        }
        // ... (similar for other edges, simplified for brevity)

        if (i % 2 == 0) // Only draw every other segment for dashed effect
            g.drawLine(startPoint.x, startPoint.y, endPoint.x, endPoint.y, stroke * 0.8f);
    }

    // Motion trail/path from source to target
    g.setColour(color.withAlpha(0.5f));
    juce::Path motionPath;
    motionPath.startNewSubPath(sourceX, sourceY);

    // Curved path to show drag motion
    auto controlX = sourceX + (targetX - sourceX) * 0.7f;
    auto controlY = sourceY - iconBounds.getHeight() * 0.2f;
    motionPath.quadraticTo(controlX, controlY, targetX, targetY);

    // Dashed motion path
    juce::Array<float> dashPattern = {stroke * 2, stroke};
    juce::Path dashedMotionPath;
    juce::PathStrokeType dashedStroke(stroke * 0.8f);
    dashedStroke.createDashedStroke(dashedMotionPath, motionPath, dashPattern.getRawDataPointer(), dashPattern.size());
    g.strokePath(dashedMotionPath, createStroke(stroke * 0.8f));

    // Arrow showing direction
    g.setColour(color.brighter(0.4f));
    auto arrowSize = stroke * 2;
    auto arrowAngle = std::atan2(targetY - controlY, targetX - controlX);
    auto arrowX = targetX - std::cos(arrowAngle) * arrowSize * 2;
    auto arrowY = targetY - std::sin(arrowAngle) * arrowSize * 2;

    juce::Path arrow;
    arrow.startNewSubPath(arrowX, arrowY);
    arrow.lineTo(arrowX - std::cos(arrowAngle - 0.3f) * arrowSize,
                arrowY - std::sin(arrowAngle - 0.3f) * arrowSize);
    arrow.lineTo(arrowX - std::cos(arrowAngle + 0.3f) * arrowSize,
                arrowY - std::sin(arrowAngle + 0.3f) * arrowSize);
    arrow.closeSubPath();

    g.fillPath(arrow);

    // Assignment symbol (equals sign or link symbol)
    g.setColour(color);
    auto assignY = iconBounds.getCentreY();
    auto assignX1 = sourceX + sourceSize * 0.7f;
    auto assignX2 = targetX - targetSize * 0.7f;
    auto assignLength = (assignX2 - assignX1) * 0.3f;
    auto assignCenterX = (assignX1 + assignX2) * 0.5f;

    // Two parallel lines for "=" symbol
    g.drawLine(assignCenterX - assignLength * 0.5f, assignY - stroke,
              assignCenterX + assignLength * 0.5f, assignY - stroke, stroke * 0.8f);
    g.drawLine(assignCenterX - assignLength * 0.5f, assignY + stroke,
              assignCenterX + assignLength * 0.5f, assignY + stroke, stroke * 0.8f);
}

void FancyIconPack::drawDragToConnect(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour color)
{
    auto iconBounds = bounds;
    auto stroke = getOptimalStrokeWidth(iconBounds);

    // Two connection points with cable/wire being dragged between them
    auto nodeRadius = juce::jmin(stroke * 2.0f, iconBounds.getWidth() * 0.08f); // Ensure reasonable size
    auto nodeSize = nodeRadius * 2;

    // Source node (left side) - ensure it's within bounds
    auto sourceX = iconBounds.getX() + nodeRadius * 1.5f;
    auto sourceY = iconBounds.getY() + iconBounds.getHeight() * 0.3f;

    g.setColour(color);
    g.fillEllipse(sourceX - nodeRadius, sourceY - nodeRadius, nodeSize, nodeSize);
    g.setColour(color.brighter(0.3f));
    g.drawEllipse(sourceX - nodeRadius, sourceY - nodeRadius, nodeSize, nodeSize, stroke * 0.8f);

    // Target node (right side) - ensure it's within bounds
    auto targetX = iconBounds.getRight() - nodeRadius * 1.5f;
    auto targetY = iconBounds.getY() + iconBounds.getHeight() * 0.8f;

    g.setColour(color.withAlpha(0.7f));
    g.drawEllipse(targetX - nodeRadius, targetY - nodeRadius, nodeSize, nodeSize, stroke);

    // Highlight target as connection destination - constrain to bounds
    g.setColour(color.brighter(0.4f));
    auto highlightRadius = juce::jmin(nodeRadius * 1.3f, iconBounds.getWidth() * 0.1f);
    g.drawEllipse(targetX - highlightRadius, targetY - highlightRadius,
                  highlightRadius * 2, highlightRadius * 2, stroke * 0.6f);

    // Connection cable/wire being dragged - keep curve within bounds
    juce::Path cable;
    cable.startNewSubPath(sourceX, sourceY);

    // Create a natural cable sag/curve - constrain to icon bounds
    auto midX = (sourceX + targetX) * 0.5f;
    auto maxSag = iconBounds.getHeight() * 0.15f; // Limit sag to stay within bounds
    auto midY = juce::jmin(juce::jmax(sourceY, targetY) + maxSag, iconBounds.getBottom() - stroke * 2);

    // Drag position (intermediate point showing active dragging) - ensure within bounds
    auto dragX = juce::jlimit(iconBounds.getX() + nodeRadius * 2, iconBounds.getRight() - nodeRadius * 2,
                             sourceX + (targetX - sourceX) * 0.7f);
    auto dragY = juce::jlimit(iconBounds.getY() + nodeRadius * 2, iconBounds.getBottom() - nodeRadius * 2,
                             sourceY + (midY - sourceY) * 0.8f);

    // Cable from source to drag position
    cable.quadraticTo(sourceX + (dragX - sourceX) * 0.5f,
                     juce::jlimit(iconBounds.getY(), iconBounds.getBottom(), midY * 0.7f),
                     dragX, dragY);

    g.setColour(color);
    g.strokePath(cable, createStroke(stroke * 1.5f));

    // Cable continuation (dashed to show intended connection)
    juce::Path cableContinuation;
    cableContinuation.startNewSubPath(dragX, dragY);
    cableContinuation.quadraticTo(dragX + (targetX - dragX) * 0.5f,
                                 juce::jlimit(iconBounds.getY(), iconBounds.getBottom(), midY),
                                 targetX, targetY);

    juce::Array<float> dashPattern = {stroke * 2, stroke};
    juce::Path dashedCable;
    juce::PathStrokeType dashedStroke(stroke);
    dashedStroke.createDashedStroke(dashedCable, cableContinuation,
                                   dashPattern.getRawDataPointer(), dashPattern.size());

    g.setColour(color.withAlpha(0.6f));
    g.strokePath(dashedCable, createStroke(stroke));

    // Cable connector/plug at the dragged end
    g.setColour(color.brighter(0.2f));
    auto plugRadius = stroke * 1.2f;
    g.fillEllipse(dragX - plugRadius, dragY - plugRadius, plugRadius * 2, plugRadius * 2);
    g.setColour(color.darker(0.2f));
    g.drawEllipse(dragX - plugRadius, dragY - plugRadius, plugRadius * 2, plugRadius * 2, stroke * 0.6f);

    // Small inner circle for plug detail
    auto innerPlugRadius = plugRadius * 0.5f;
    g.setColour(color.contrasting(0.6f));
    g.fillEllipse(dragX - innerPlugRadius, dragY - innerPlugRadius,
                  innerPlugRadius * 2, innerPlugRadius * 2);

    // Motion indicators (small lines showing drag movement) - constrain to bounds
    g.setColour(color.withAlpha(0.5f));
    auto motionLineCount = 3;
    for (int i = 0; i < motionLineCount; ++i)
    {
        auto lineLength = stroke * (1 + i * 0.5f);
        auto lineOffset = stroke * (1 + i);
        auto lineX = juce::jmax(iconBounds.getX(), dragX - lineOffset);
        auto lineY = juce::jlimit(iconBounds.getY(), iconBounds.getBottom() - stroke,
                                 dragY + i * stroke * 0.5f);
        auto lineEndX = juce::jmin(iconBounds.getRight(), lineX + lineLength);

        // Only draw if the line would be visible within bounds
        if (lineX < iconBounds.getRight() && lineEndX > iconBounds.getX())
        {
            g.drawLine(lineX, lineY, lineEndX, lineY, stroke * 0.5f);
        }
    }

    // Connection success indicator (optional visual feedback) - constrain sparks to bounds
    if (true) // Could be state-dependent
    {
        g.setColour(color.brighter(0.5f));
        auto sparkCount = 4;
        auto maxSparkRadius = juce::jmin(nodeRadius * 1.5f,
                                        juce::jmin(targetX - iconBounds.getX(),
                                                  iconBounds.getRight() - targetX) * 0.8f);

        for (int i = 0; i < sparkCount; ++i)
        {
            auto angle = (i / static_cast<float>(sparkCount)) * juce::MathConstants<float>::twoPi;
            auto sparkX = targetX + std::cos(angle) * maxSparkRadius;
            auto sparkY = targetY + std::sin(angle) * maxSparkRadius;
            auto sparkSize = stroke * 0.6f;

            // Only draw sparks that are within icon bounds
            if (sparkX >= iconBounds.getX() && sparkX <= iconBounds.getRight() &&
                sparkY >= iconBounds.getY() && sparkY <= iconBounds.getBottom())
            {
                g.drawLine(sparkX - sparkSize, sparkY, sparkX + sparkSize, sparkY, stroke * 0.4f);
                g.drawLine(sparkX, sparkY - sparkSize, sparkX, sparkY + sparkSize, stroke * 0.4f);
            }
        }
    }
}
