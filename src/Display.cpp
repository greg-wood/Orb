#include "Display.hpp"
#include "Messages.hpp"

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(
    U8G2_R0, /* reset=*/U8X8_PIN_NONE, /* clock=*/4, /* data=*/5);

void setupDisplay()
{
    u8g2.begin();
}

int currentAnswerIndex = -1;
void drawWrappedCenteredText(const char *text, int maxWidth, int lineHeight, int screenHeight)
{
    char buffer[256];
    strncpy(buffer, text, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char *word = strtok(buffer, " ");
    String line = "";
    std::vector<String> lines;

    // First pass: wrap lines
    while (word != nullptr)
    {
        String testLine = line + word + " ";
        int width = u8g2.getUTF8Width(testLine.c_str());

        if (width > maxWidth && !line.isEmpty())
        {
            lines.push_back(line);
            line = String(word) + " ";
        }
        else
        {
            line = testLine;
        }
        word = strtok(nullptr, " ");
    }

    if (!line.isEmpty())
    {
        lines.push_back(line);
    }

    // Calculate vertical start position for centering
    int totalHeight = lines.size() * lineHeight;
    int y = (screenHeight - totalHeight) / 2 + lineHeight; // center vertically

    // Draw each line centered
    for (const auto &ln : lines)
    {
        int textWidth = u8g2.getUTF8Width(ln.c_str());
        int x = (128 - textWidth) / 2; // center horizontally
        u8g2.drawUTF8(x, y, ln.c_str());
        y += lineHeight;
    }
}

void show8BallResponse()
{
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB08_tr);

    int index = random(0, sizeof(answers) / sizeof(answers[0]));
    const char *message = answers[index];

    drawWrappedCenteredText(message, 128, 12, 64); // screen width, line height, screen height
    u8g2.sendBuffer();

    Serial.println("Displayed: " + String(message));
}
