#include <Arduino.h>
 #include <vector> 
#include <Wire.h>
#include <U8g2lib.h>
#include "esp_sleep.h"
#include "driver/gpio.h"
 #include <WiFi.h>
    #include <ArduinoOTA.h>
#include <ESPmDNS.h>


#define TAP_GPIO 3  // GPIO connected to tap module
#define TAP_PIN_MASK (1ULL << TAP_GPIO)

   const char* ssid = "WoodPrivate";
    const char* password = "woodgreg";

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(
  U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 4, /* data=*/ 5
);

// Cursed responses
const char* answers[] = {
  "Doom awaits", "You shouldn't have asked", "Run.",
  "Absolutely cursed", "Spirits say no", "Your fate is sealed",
  "Yes... but at what cost?", "He sees you now",
  "Microwave your socks.", "Drink water... from a puddle.",
  "Lick a 9V battery for good luck.", "Yes. But do it blindfolded.",
  "Eat spaghetti with scissors.", "Paint your ceiling with ketchup.",
  "Charge your phone in the microwave.", "Buy a ferret. Name it CEO.",
  "Touch the red wire.", "Stand in a lightning storm to assert dominance.",
  "Solder with your eyes closed.", "Stick a fork in philosophy.",
  "Boil soda. In your bedroom.", "Put your hand in a toaster. For science.",
  "Enable root access to your houseplants.", "Update BIOS mid-flight.",
  "He knows you're watching.", "Do NOT look behind you.",
  "The ritual begins at 3:17 AM.", "Say your IP out loud.",
  "Unplug your router and summon him.", "Burn a USB stick under the full moon.",
  "He awakens when the battery dies.", "You've already been chosen.",
  "Message your ex: 'I forgive you.' Then block them.",
  "Invest in raccoon futures.", "Tell your boss 'I understand the mission.' Then leave.",
  "Flush exactly 37 ice cubes.", "Rename your Wi-Fi 'NSA Surveillance Van'.",
  "Apply for a mortgage using crayon.", "Replace your doorbell with a scream.mp3.",
  "Contact your ex.", "Buy 12 cats.", "Text your boss 'u up?'", "Touch the stove.",
  "Engage airplane mode IRL.", "Reformat your brain.",
  "Quit your job. Become a SoundCloud rapper.",
  "Stop watching YouTube and go outside.",
  "File your taxes in crayon.",
  "The goat has been sacrificed.", "The wires are humming in agreement.",
  "The council screeched, then nodded.", "All systems are blinking green… and red.",
  "A strange warmth fills the room.", "The machine smiled. That's rare.",
  "The prophecy just updated.", "You already started, didn't you?",
  "The void cracked a smile.", "Your toaster lit up in approval.",
  "It's too late to back out now.", "The pigeons are circling supportively.",
  "The circuits didn't scream this time.", "The simulation gave a thumbs-up.",
  "A door just unlocked somewhere.", "The vibes said 'fine, whatever'.",
  "The battery sparked like it meant yes.", "Even the cursed dice agree.",
  "A raccoon just gave you a high five.", "A rubber duck just blinked twice.",
  "The spirits are concerned.", "A cold wind just blew through your router.",
  "That action is illegal in three realities.", "The fridge stopped humming.",
  "Even the cursed one recoiled.", "Your shadow just twitched.",
  "Unmarked vans are already on the way.", "The air feels... judgmental.",
  "The crystal cracked in protest.", "Something blinked... and then stopped.",
  "A cat hissed without reason.", "The lights dimmed when you asked.",
  "A low growl came from your motherboard.", "Time stuttered briefly.",
  "The fortune cookie was empty.", "The static is getting louder.",
  "The AI paused... too long.", "The door locked itself.",
  "Three ravens turned away.", "The cursor moved on its own.",
  "The stars are buffering.", "The answer fell between the cracks.",
  "Consult your alternate self.", "The chicken didn't cross the road today.",
  "The universe shrugged again.", "Results pending... forever.",
  "The coffee grounds were inconclusive.", "A coin landed on its edge.",
  "The response is trapped in another tab.", "The algorithm twitched.",
  "A whisper said 'ehhh... maybe?'", "The code compiled with warnings.",
  "Someone rolled a 7 on a 6-sided die.", "The vibes are in beta.",
  "Time skipped a beat.", "The sky blinked twice, then stopped.",
  "The response is locked behind DLC.", "A loading bar appeared and disappeared.",
  "The dice caught fire mid-roll.", "The ethernet cable curled in fear.",
  "Become nocturnal.", "Install Windows ME on purpose.",
  "Declare yourself a deity on Facebook.", "Make eye contact with a crow.",
  "Eat an HDMI cable.", "Tell your plants your secrets.",
  "Trust no printers.", "Marry a traffic cone.",
  "Enable JavaScript in real life.", "Download more RAM from eBay.",
  "Fight your thermostat for dominance.", "Name your child 'NullPointer'.",
  "Yell 'enhance' at security footage.", "Store passwords in plaintext tattoos.",
  "Befriend your microwave.", "Move to Ohio. Don't ask why.",
  "Rename your cat '404'.", "Open 100 Chrome tabs. For power.",
  "Join a pyramid scheme ironically.", "Replace your mouse with a potato.",
  "Make a salad in your sink.", "Code in Comic Sans.",
  "Tell Alexa your fears.", "Install a speaker in your toilet.",
  "Unironically buy a fax machine.", "Run a server from a toaster.",
  "Hack the moon. You won't.", "Send snail mail to Elon Musk.",
  "Only speak in SQL commands.", "Charge your vape with solar panels.",
  "Forge a sword. Name it 'Regret'.", "Reboot your soul.",
  "Blink once for help. Blink twice for chaos.",
  "Use duct tape as currency.", "Adopt a goat. Name it VPN.",
  "Summon Clippy with forbidden code.", "Reset factory settings. On yourself.",
  "Sneeze into the void.", "Leave an AirTag in a cursed forest.",
  "Run Doom on your fridge.", "Eat a USB stick for breakfast.",
  "Switch to rotary phone texting.", "Debug your emotions.",
  "Sacrifice your microwave for better WiFi.", "Apply thermal paste to your teeth.",
  "Rent a llama on Craigslist.", "Pledge allegiance to static electricity.",
  "Build a trebuchet. Use it immediately.",
  "Whisper secrets to your hard drive.", "Ask ChatGPT for parenting advice.",
  "Hold your breath until Java compiles.", "Tell your boss you're becoming vapor.",
  "Reboot the simulation.", "Paint your room in binary.",
  "Trust the raccoons.", "Measure time in chicken nuggets.",
  "Text 'I'm ready' to the unknown number.", "Challenge gravity to a duel.",
  "Install Linux on a toaster oven.", "Hack your own dreams.",
  "Leave your house and never return.", "Make a pie chart of regrets.",
  "Microwave your resume.", "Use bubble wrap as armor.",
  "Fight a goose for dominance.", "Replace all apps with MS Paint.",
  "Download emotions illegally.", "Whistle at drones.",
  "Use your fridge as a diary.", "Meditate with static noise.",
  "Accept cookies in real life.", "Cut your own Ethernet cable. Spiritually.",
  "Convert your car to JavaScript.", "Host a LAN party in the woods.",
  "Rent a server on the dark web.", "Make eye contact with your toaster.",
  "Trust the blinking LED.", "Store your feelings in an Excel sheet.",
  "Tattoo your IP address.", "Whisper 'sudo' before major decisions.",
  "Change your name to Ctrl+Z.", "Sacrifice bandwidth to the algorithm.",
  "Leave milk out for the GPU spirits.", "Marry a CAPTCHA.",
  "Buy expired RAM on Craigslist.", "Encrypt your diary.",
  "Install ad blockers in your brain.", "Turn on airplane mode during takeoff.",
  "Say 'OK Google' to the void.", "Scan your soul for viruses.",
  "Post your heartbeat to Twitter.", "Update your firmware at midnight.",
  "Join a cult. Start your own.", "Code until the voices stop.",
  "Ask Siri about the afterlife.", "Declare war on PowerPoint.",
  "Delete system32 emotionally.", "Outsource your dreams to AI.",
  "Install a firewall in your shower.", "You're not ready, but do it anyway.",
  "This is how legends begin. And end.", "Proceed, preferably with goggles.",
  "It is... statistically possible.", "The stars shrugged.",
  "What could possibly go wrong?", "You're legally allowed to.",
  "Just sign the waiver first.",
  "That would anger the garden gnome.",
  "Someone in Ohio just felt that.",
  "It's happening again.",
  "The raccoons have noticed.", "Time is... bending.",
  "You heard the whispers too?", "A shadow just moved.",
  "The moon blinked.", "Ask your blender.",
  "Upload your soul first.", "Yes, but only in a parallel timeline.",
  "The crab union disapproves.", "Fortnite says otherwise.",
  "Your microwave just nodded.", "Not even ChatGPT would do that.",
  "You're gonna need more duct tape.", "Unplug your fridge. Now.",
  "There's no going back now.", "The ritual has begun.",
  "Step outside. Bring salt.", "Reality is soft today.",
  "Consult the duck first.", "That would void your warranty.",
  "The orb pulses with energy.", "Error: Morality not found.",
  "Too late. It's already in motion.", "Yes, but you'll owe the rats a favor.",
  "Application denied by Entity-42.", "Approval pending further chaos.",
  "Request rerouted to Basement Division.", "Your inquiry has been logged... by Them.",
  "Try again after the lunar audit.", "That exceeds your allowed entropy quota.",
  "You'll need a permission slip signed in blood.", "Currently under investigation.",
  "Your destiny is in a queue.", "Paperwork has been misplaced. Oops.",
  "Trust your worst instincts.", "That's the best bad idea I've heard.",
  "Technically legal in 3 states.", "Do it for the plot.",
  "As long as no one finds out.", "That's exactly how legends get arrested.",
  "One way to make memories.", "That's the spirit. Probably a bad one.",
  "No refunds on consequences.", "Perfect. Now ignite the cheese.",
  ">> [Signal lost] <<", "404: Answer Not Found", "YES??no??maybe??YES??",
  "[REDACTED BY ORDER OF THE VOID]", "Data corrupted. Consult the toaster.",
  "|| Transmission unstable ||", "--Protocol breached--",
  "Echo detected… echo detected…", "RUN.exe triggered",
  "[Unknown entity detected]", "That depends on the alignment of three moons you've never heard of.",
  "Someone already knows the answer. You just haven't met them yet.",
  "It's buried beneath layers of nachos and regret.",
  "You'll know when the toaster screams.", "The answer is wearing a disguise.",
  "Check behind the fourth wall.", "You're asking the right questions. The wrong way.",
  "It's been inside you all along… like a parasite.",
  "Not yet. The algorithm isn't done learning you.",
  "Yes, but only if you embrace the chaos.",
  "The path is unclear, but your shoes are on the wrong feet.",
  "Love? Meaning? Try caffeine and panic instead.",
  "Only if the raccoons allow it.", "You'll find out the moment it's too late to change.",
  "The answer is shaped like a duck, metaphorically.",
  "Someone in this room already knows.",
  "It's complicated. Like your browser history.",
  "It ends in fire. But like, emotionally.",
  "When the stars align, and your Wi-Fi disconnects.",
  "You'll understand… eventually. Maybe.",
  "The truth wears Crocs and drinks warm milk.",
  "Even Schrödinger's cat is confused.",
  "Try turning yourself off and on again.",
  "The universe is typing...", "Your destiny just unfollowed you.",
  "Define 'true' and 'love' first.",
  "That's a weird way to summon a cryptid.",
  "As meaningful as a microwave beep at 3AM.",
  "Somewhere between a hug and a restraining order.",
  "Ask again after the next simulation reboot.",
  "The meaning of life is probably under your couch.",
  "Love is real. Just not for you. (Yet?)",
  "You've already passed it and didn't notice.",
  "The prophecy was unclear on that part.",
  "Search your feelings. Then Google it.",
  "It's on sale next Tuesday.",
  "Yes. But you'll owe the moon a favor.",
  "You are the subplot in someone else's romance arc.",
  "Honestly? That's above my pay grade.",
  "The silence is your answer.", "Not in this timeline.",
  "You already missed your chance.", "The door is closing. Fast.",
  "You were warned.", "It's too late to change course now.",
  "He's watching.", "The shadows grow closer.",
  "This path ends poorly.", "Something has been awoken.",
  "Regret is inevitable.", "You're not ready for the truth.",
  "That will cost more than you expect.", "Even now, they're listening.",
  "The answer lies beneath the floorboards.", "Pain is part of the process.",
  "You should have stayed quiet.", "The price must be paid.",
  "You won't like what you find.", "It's coming. Slowly. Surely.",
  "No one escapes this.", "You weren't meant to ask that.",
  "This was a mistake.", "The void responds... but with laughter.",
  "You're running out of time.", "Fate frowns upon this.",
  "You can't undo what's begun.", "It hears you.",
  "There is no safe choice.", "This will echo forever.",
  "Even hope has abandoned you.", "It was never meant for you.",
  "You're not alone. And that's worse.", "Sleep won't help.",
  "Something waits beneath the surface.", "The walls are closing in.",
  "Your reflection knows more than it should.", "Soon, but not soon enough to help.",
  "Everything is temporary. Especially you.", "They've already decided your fate.",
  "You are the final variable.", "The storm has noticed you.",
  "You're asking the wrong questions.", "It ends where it began. Badly.",
  "Trust no mirrors today.", "Your luck just expired.",
  "They remember what you did.", "You've been marked.",
  "That choice cannot be unmade.", "There is no answer. Only consequence.",
  "You already made that mistake twice.",
    "The void winked back.",
    "It ends in flames. Probably yours.",
    "Ask again after the next blood moon.",
    "You've angered something older than consequence.",
    "There's a knock coming. Don't answer it.",
    "The floor beneath you remembers.",
    "Hope is a scam. Proceed anyway.",
    "The bones say no. Loudly.",
    "Your shadow flinched first.",
    "Dig deeper. It's not buried yet.",
    "You're past the point of safe choices.",
    "The contract was signed in breath, not ink.",
    "Someone else paid for your luck.",
    "The alarm didn't go off for a reason.",
    "This timeline is already cracked.",
    "Try fire. Try more fire.",
    "You can't outrun this one barefoot.",
    "It screamed when you looked away.",
    "Even the mirror lied this time.",
    "That price isn't in currency.",
    "The storm was listening.",
    "You were never the protagonist.",
    "Ask the one behind your second thought.",
    "You blinked at the wrong ritual.",
    "He already knows you're coming.",
    "Nothing survives the third option.",
    "Bury the evidence. Then forget where.",
    "It ends with teeth. Not yours.",
    "The safe word was overwritten.",
    "The last witness recanted. Then vanished.",
    "Yes, but only if you don't survive it.",
    "The blood under your fingernails remembers.",
    "There was never a 'Plan A'.",
    "You're the reason it wakes up.",
    "Hope packed up last Thursday.",
    "You've seen too much. Again.",
    "There's a file with your name on it. Burning.",
    "Run. Then run weirder.",
    "That scream wasn't external.",
    "You passed. The trap was optional.",
    "You're on your own, and it knows.",
    "Ask forgiveness, not directions.",
    "You're on thin time, not thin ice.",
    "The last deal broke reality.",
    "You're in the splash zone of destiny.",
    "It's already behind you.",
    "Only fools and martyrs continue now.",
    "The walls are learning your name.",
    "Regret is part of the recipe.",
    "Do it. But not here.",
    "You're still being watched. Closely.",
    "It's your move, chaos is waiting.",
    "Break the mirror and talk to her.",
    "The exit was never marked.",
    "The silence is loaded.",
    "The rules changed during your nap.",
    "Yes, but you'll owe more than you gain.",
    "The crows have jurisdiction now.",
    "Time hiccuped. You fell out.",
    "Your secrets are leaking.",
    "Your reflection has plans.",
    "That was the last warning.",
    "It doesn't care about your intentions.",
    "Try again, this time with consequences.",
    "You were warned in a dream you forgot.",
    "You misread the blood pattern.",
    "Someone else paid, but you're collecting.",
    "It's only treason if they catch you.",
    "There's no undo button in real life.",
    "Burn the map. The path is wrong.",
    "The veil is too thin here.",
    "You've activated the bad timeline.",
    "The gods you pray to are bored.",
    "Dig up what you buried emotionally.",
    "You're about three regrets too late.",
    "Your comfort zone has been compromised.",
    "Yes, but the fallout's personal.",
    "You crossed the line four realities ago.",
    "They put your name on the list. Twice.",
    "You've been playing the decoy all along.",
    "You inherited the debt, not the fortune.",
    "Don't check your inbox. Ever.",
    "That ritual wasn't symbolic.",
    "You'll walk out changed. Not improved.",
    "Try asking with your real name this time.",
    "The exit fee is your peace of mind.",
    "That wasn't thunder. It was a door.",
    "What you just heard wasn't in your head.",
    "Regret is the best-case outcome.",
    "You're not the first to ask this.",
    "That noise was foreshadowing.",
    "It only hurts if you remember.",
    "The stars blinked. That's not good.",
    "Ask again. Louder. The abyss is old.",
    "You've stepped off the moral grid.",
    "There's a splinter in your destiny.",
    "The choice is yours. So is the ruin.",
    "You already know. You just won't admit it.",
    "Even chaos has standards.",
    "You'll need more than guts this time.",
    "The answer costs a piece of you.",
    "Smile. It confuses the endgame.",
    "Jackson Loves Miles",
    "Nana Loves Pops",
    "No Game until homework is done"
  };



int currentAnswerIndex = -1;
void drawWrappedCenteredText(const char* text, int maxWidth, int lineHeight, int screenHeight) {
  char buffer[256];
  strncpy(buffer, text, sizeof(buffer));
  buffer[sizeof(buffer) - 1] = '\0';

  char* word = strtok(buffer, " ");
  String line = "";
  std::vector<String> lines;

  // First pass: wrap lines
  while (word != nullptr) {
    String testLine = line + word + " ";
    int width = u8g2.getUTF8Width(testLine.c_str());

    if (width > maxWidth && !line.isEmpty()) {
      lines.push_back(line);
      line = String(word) + " ";
    } else {
      line = testLine;
    }
    word = strtok(nullptr, " ");
  }

  if (!line.isEmpty()) {
    lines.push_back(line);
  }

  // Calculate vertical start position for centering
  int totalHeight = lines.size() * lineHeight;
  int y = (screenHeight - totalHeight) / 2 + lineHeight;  // center vertically

  // Draw each line centered
  for (const auto& ln : lines) {
    int textWidth = u8g2.getUTF8Width(ln.c_str());
    int x = (128 - textWidth) / 2;  // center horizontally
    u8g2.drawUTF8(x, y, ln.c_str());
    y += lineHeight;
  }
}



void show8BallResponse() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvB08_tr);

  int index = random(0, sizeof(answers) / sizeof(answers[0]));
  const char* message = answers[index];

  drawWrappedCenteredText(message, 128, 12, 64); // screen width, line height, screen height
  u8g2.sendBuffer();

  Serial.println("Displayed: " + String(message));
}




void goToSleep() {
  Serial.println("Going to sleep...");

  u8g2.clearDisplay();
  u8g2.sleepOn();
  delay(100);

  gpio_hold_en((gpio_num_t)TAP_GPIO);       // Keep pull state during sleep
  gpio_pullup_en((gpio_num_t)TAP_GPIO);     // Ensure the pin stays HIGH when idle

  esp_deep_sleep_enable_gpio_wakeup(TAP_PIN_MASK, ESP_GPIO_WAKEUP_GPIO_LOW);
  esp_deep_sleep_start();
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Booting...");
  delay (1000);

       WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);

      for(int loop=0;loop<100;loop++)  {

        Serial.print(".");
    
       if ((WiFi.status() == WL_CONNECTED))
       {
      Serial.println("\nConnected to WiFi");
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());

  // Initialize mDNS
  if (!MDNS.begin("Orb.local")) {   // Set the hostname to "esp32.local"
    Serial.println("Error setting up MDNS responder!");
    while(1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
  

      ArduinoOTA.onStart([]() {
        Serial.println("OTA Start");
      });
      ArduinoOTA.onEnd([]() {
        Serial.println("\nOTA End");
      });
      ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        // Handle specific errors if needed
      });
      ArduinoOTA.begin();
    
  u8g2.begin();

  pinMode(TAP_GPIO, INPUT_PULLUP);  // HIGH by default
  gpio_pullup_en((gpio_num_t)TAP_GPIO);

  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_GPIO) {
    Serial.println("Woken by tap!");
  } else {
    Serial.println("Normal boot.");
  }

  show8BallResponse();
  for (int loop = 0; loop < 10; loop++) {
    
  ArduinoOTA.handle();
  delay(100);  // Short delay just for demo
  }
  //goToSleep();
  delay(2000); // Show the answer for 2 seconds before sleeping
  break;
       }

else {
      Serial.println("\nFailed to connect to WiFi");
    }
      }
    }

void loop() {
delay(1000);
Serial.println("Stuck in Loop");
}
