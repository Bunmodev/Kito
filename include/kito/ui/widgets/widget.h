#pragma once
#include <vector>
#include <memory>
#include <string>
#include <SDL3/SDL.h>
#include <algorithm>
#include <kito/core/events.h>
#include <kito/ui/style/types.h>


namespace kito::Graphics {
    class Renderer;
}

namespace kito::ui {

    struct Rect {
        float x, y, width, height;
        bool contains(float px, float py) const;
    };

    struct Margin {
        float left, right, top, bottom;
    };

    struct Border {
        float width;
        SDL_Color color;
    };

    struct Padding {
        float left, right, top, bottom;
    };

    struct Content {
        float x, y, width, height;
    };

    struct Display {
        std::string type;
    };

    struct DesiredDimensions {
        int width = 0;
        int height = 0;
    };

    struct Style {
        Spacing padding;
        Spacing margin;

        int width, height;
        
        struct Grid {
            int gridCols = 4;
            int columnGap = 2;
            int rowGap = 2;
            int gridRows = 0;
            
            struct GridCell {
                int width;
                int height;
            } gridCell;

        } grid;

        int gap;
        std::string background_color;
    };

    class Widget {
        protected:
            Rect bounds;
            Rect baseBounds;
            Rect contentBounds;

            bool visible = true;
            bool enabled = true;

            std::string id;

            Widget* parent = nullptr;
            std::vector<std::unique_ptr<Widget>> children;

            Margin margin;
            Border border;
            Padding padding;
            Content content;

            Display display;

            DesiredDimensions desiredDimensions;

            Style style;

        public:
            Widget(std::string id, Rect rect);
            virtual ~Widget();

            virtual void update(float deltaTime);

            virtual void draw(kito::Graphics::Renderer& renderer) = 0;
            virtual void handleEvent(const KitoEvent& event) = 0;

            virtual void setAttribute(const std::string& name, const std::string& value);

            virtual bool handleMouseClick(SDL_Event& event, float x, float y);

            const SDL_Rect getRect() const;
            SDL_Rect setRect(float x, float y, float w, float h);

            Rect getBaseBounds() const;
            Rect getBounds() const;

            Rect getContentBounds() const;

            void updateContentBounds(float x, float y, float w, float h);
            void updateComputedBounds(float x, float y, float w, float h);

            std::string getId() const;

            Widget* getParent() const;
            
            Widget* findTarget(float x, float y);

            void addChild(std::unique_ptr<Widget> child);
            const std::vector<std::unique_ptr<Widget>>& getChildren() const;

            virtual void onClick();

            void setBorder(float width, SDL_Color color);
            Border getBorder() const;

            void setMargin(float left, float right, float top, float bottom);
            Margin getMargin() const;

            Padding getPadding() const;
            void setPadding(float left, float right, float top, float bottom);

            Content getContent() const;
            void setContent(float width, float height);

            Display getDisplay() const;
            void setDisplay(std::string displayType);

            DesiredDimensions getDesiredDimensions() const;
            void setDesiredDimensions(int width, int height);

            Style getBakedStyle() const;

            bool isHit(float px, float py) const;
    };

}
