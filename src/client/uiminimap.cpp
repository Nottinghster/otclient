/*
 * Copyright (c) 2010-2025 OTClient <https://github.com/edubart/otclient>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "uiminimap.h"
#include "game.h"
#include "luavaluecasts_client.h"

#include "minimap.h"
#include "uimapanchorlayout.h"

void UIMinimap::drawSelf(const DrawPoolType drawPane)
{
    UIWidget::drawSelf(drawPane);
    if (drawPane != DrawPoolType::FOREGROUND)
        return;

    if (!m_layout)
        m_layout = std::make_shared<UIMapAnchorLayout>(static_self_cast<UIWidget>());

    g_minimap.draw(getPaddingRect(), m_cameraPosition, m_scale, m_color);
}

bool UIMinimap::setZoom(const int8_t zoom)
{
    if (zoom == m_zoom)
        return true;

    if (zoom < m_minZoom || zoom > m_maxZoom)
        return false;

    const int oldZoom = m_zoom;
    m_zoom = zoom;

    m_scale = 1.f;

    if (m_zoom < 0)
        m_scale /= 1 << std::abs(zoom);
    else if (m_zoom > 0)
        m_scale *= 1 << std::abs(zoom);

    if (m_layout)
        m_layout->update();

    onZoomChange(zoom, oldZoom);
    return true;
}

void UIMinimap::setCameraPosition(const Position& pos)
{
    if (m_cameraPosition == pos)
        return;

    const Position oldPos = m_cameraPosition;
    m_cameraPosition = pos;

    if (m_layout)
        m_layout->update();

    onCameraPositionChange(pos, oldPos);
}

bool UIMinimap::floorUp()
{
    Position pos = m_cameraPosition;
    if (!pos.up())
        return false;

    setCameraPosition(pos);
    return true;
}

bool UIMinimap::floorDown()
{
    Position pos = m_cameraPosition;
    if (!pos.down())
        return false;
    setCameraPosition(pos);
    return true;
}

Point UIMinimap::getTilePoint(const Position& pos)
{
    return g_minimap.getTilePoint(pos, getPaddingRect(), m_cameraPosition, m_scale);
}

Rect UIMinimap::getTileRect(const Position& pos)
{
    return g_minimap.getTileRect(pos, getPaddingRect(), m_cameraPosition, m_scale);
}

Position UIMinimap::getTilePosition(const Point& mousePos)
{
    return g_minimap.getTilePosition(mousePos, getPaddingRect(), m_cameraPosition, m_scale);
}

void UIMinimap::anchorPosition(const UIWidgetPtr& anchoredWidget, const Fw::AnchorEdge anchoredEdge, const Position& hookedPosition, const Fw::AnchorEdge hookedEdge)
{
    if (!m_layout)
        return;

    const auto& layout = m_layout->static_self_cast<UIMapAnchorLayout>();
    assert(layout);
    layout->addPositionAnchor(anchoredWidget, anchoredEdge, hookedPosition, hookedEdge);
}

void UIMinimap::fillPosition(const UIWidgetPtr& anchoredWidget, const Position& hookedPosition)
{
    if (!m_layout)
        return;

    const auto& layout = m_layout->static_self_cast<UIMapAnchorLayout>();
    assert(layout);
    layout->fillPosition(anchoredWidget, hookedPosition);
}

void UIMinimap::centerInPosition(const UIWidgetPtr& anchoredWidget, const Position& hookedPosition)
{
    if (!m_layout)
        return;

    const auto& layout = m_layout->static_self_cast<UIMapAnchorLayout>();
    assert(layout);
    layout->centerInPosition(anchoredWidget, hookedPosition);
}

void UIMinimap::onZoomChange(const int zoom, const int oldZoom) { callLuaField("onZoomChange", zoom, oldZoom); }

void UIMinimap::onCameraPositionChange(const Position& position, const Position& oldPosition) { callLuaField("onCameraPositionChange", position, oldPosition); }

void UIMinimap::onStyleApply(const std::string_view styleName, const OTMLNodePtr& styleNode)
{
    UIWidget::onStyleApply(styleName, styleNode);
    for (const auto& node : styleNode->children()) {
        if (node->tag() == "zoom")
            setZoom(node->value<int>());
        else if (node->tag() == "max-zoom")
            setMaxZoom(node->value<int>());
        else if (node->tag() == "min-zoom")
            setMinZoom(node->value<int>());
    }
}