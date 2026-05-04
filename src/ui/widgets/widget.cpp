#include <kito/ui/widgets/widget.h>

using namespace kito::ui;

bool Rect::contains(float px, float py) const {
    return px >= x && px <= x + width &&
           py >= y && py <= y + height;
}

Widget::Widget(std::string id, Rect rect)
    : id(std::move(id)), bounds(rect), baseBounds(rect) {}

Widget::~Widget() = default;

void Widget::update(float deltaTime) {
    for (auto& child : children) {
        if (child->enabled)
            child->update(deltaTime);
    }
}

void Widget::setAttribute(const std::string&, const std::string&) {}

bool Widget::handleMouseClick(SDL_Event& event, float x, float y) {
    if (!visible || !enabled || !bounds.contains(x, y))
        return false;

    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        if ((*it)->handleMouseClick(event, x, y))
            return true;
    }

    onClick();
    return true;
}

const SDL_Rect Widget::getRect() const {
    return SDL_Rect{
        static_cast<int>(bounds.x),
        static_cast<int>(bounds.y),
        static_cast<int>(bounds.width),
        static_cast<int>(bounds.height)
    };
}

SDL_Rect Widget::setRect(float x, float y, float w, float h) {
    bounds.x = x;
    bounds.y = y;
    bounds.width = w;
    bounds.height = h;
    return getRect();
}

Rect Widget::getBaseBounds() const { return baseBounds; }

Rect Widget::getBounds() const { return bounds; }

Rect Widget::getContentBounds() const { return contentBounds; }

void Widget::updateContentBounds(float x, float y, float w, float h) {
    contentBounds.x = x;
    contentBounds.y = y;
    contentBounds.width = w;
    contentBounds.height = h;
}

void Widget::updateComputedBounds(float x, float y, float w, float h) {
    bounds.x = x;
    bounds.y = y;
    bounds.width = w;
    bounds.height = h;
}

std::string Widget::getId() const { return id; }

Widget* Widget::getParent() const { return parent; }

void Widget::addChild(std::unique_ptr<Widget> child) {
    child->parent = this;
    children.push_back(std::move(child));
}

const std::vector<std::unique_ptr<Widget>>& Widget::getChildren() const {
    return children;
}

void Widget::onClick() {}

void Widget::setBorder(float width, SDL_Color color) {
    border.width = width;
    border.color = color;
}

Border Widget::getBorder() const { return border; }

void Widget::setMargin(float left, float right, float top, float bottom) {
    margin.left = left;
    margin.right = right;
    margin.top = top;
    margin.bottom = bottom;
}

Margin Widget::getMargin() const { return margin; }

Padding Widget::getPadding() const { return padding; }

void Widget::setPadding(float left, float right, float top, float bottom) {
    padding.left = left;
    padding.right = right;
    padding.top = top;
    padding.bottom = bottom;
}

Content Widget::getContent() const { return content; }

void Widget::setContent(float width, float height) {
    content.width = width;
    content.height = height;
}

Display Widget::getDisplay() const { return display; }

void Widget::setDisplay(std::string displayType) {
    if(displayType == "grid") display.type = "grid";
    else if(displayType == "flex") display.type = "flex";
    else if(displayType == "linear") display.type = "linear";
    else display.type = "block";
}

DesiredDimensions Widget::getDesiredDimensions() const { return desiredDimensions; };

void Widget::setDesiredDimensions(int width, int height) {
    desiredDimensions.width = width;
    desiredDimensions.height = height;
}

Style Widget::getBakedStyle() const { return style; };


bool Widget::isHit(float px, float py) const {
    // Reuses the Rect::contains method you already defined
    return bounds.contains(px, py);
}

// In Widget.cpp
Widget* Widget::findTarget(float x, float y) {
    // 1. Basic Guard (Visibility and Bounds)
    if (!visible || !enabled || !bounds.contains(x, y)) {
        return nullptr;
    }

    // 2. Recursive Check: Look at children in REVERSE (top-most Z-order first)
    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        Widget* target = (*it)->findTarget(x, y);
        if (target) return target; // A child (like a button) was hit
    }

    // 3. Leaf Hit: No children were hit, so the click is on this widget itself
    return this; 
}

