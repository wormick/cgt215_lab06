#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main() {
    string background = "images1/backgrounds/winter.png";
    string foreground = "images1/characters/Rey_green_screen.png";
    Texture backgroundTex;
    if (!backgroundTex.loadFromFile(background)) {
        cout << "Couldn't Load Background Image" << endl;
        exit(1);
    }

    Texture foregroundTex;
    if (!foregroundTex.loadFromFile(foreground)) {
        cout << "Couldn't Load Foreground Image" << endl;
        exit(1);
    }

    Image backgroundImage;
    backgroundImage = backgroundTex.copyToImage();
    Image foregroundImage;
    foregroundImage = foregroundTex.copyToImage();
    Vector2u sz = backgroundImage.getSize();

    Color chromaKeyColor(16, 244, 22);

    for (int y = 0; y < sz.y; y++) {
        for (int x = 0; x < sz.x; x++) {
            Color pixelColor = foregroundImage.getPixel(x, y);

            if (pixelColor == chromaKeyColor) {
                pixelColor.a = 0;
                foregroundImage.setPixel(x, y, pixelColor);
            }
        }
    }

    RenderWindow window(VideoMode(1024, 768), "Here's the output");

    //background image
    Sprite backgroundSprite;
    Texture backgroundTexture;
    backgroundTexture.loadFromImage(backgroundImage);
    backgroundSprite.setTexture(backgroundTexture);

    //foreground image
    Sprite foregroundSprite;
    Texture foregroundTexture;
    foregroundTexture.loadFromImage(foregroundImage);
    foregroundSprite.setTexture(foregroundTexture);

    window.clear();
    window.draw(backgroundSprite);
    window.draw(foregroundSprite);
    window.display();
    while (true);

    return 0;
}