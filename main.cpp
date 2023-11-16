#include <iostream>

#include "vcpkg/Telegram-Bot-Api-Cpp/telegram/include/TelegramAPI.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    TgBot::Bot bot("API Key Here"); // Подставьте свой ключ API
    bot.getApi().deleteWebhook();
    TgBot::Message::Ptr message;
    int update_id = 0;
    while (true) {
        vector<TgBot::Update> updates = bot.getApi().getUpdates(update_id);
        for (const auto& update : updates) {
            if (update.message) {
                message = update.message;
                cout << "Message from " << message->from->firstName<< ": " <<
                     message->text << endl;
                bot.getApi().sendMessage(message->chat->id, "I'm here to help!");
            }
            update_id = update.updateId + 1;
        }
    }
    return 0;
}
void sendSomething(const Telegram::Bot::Types::API &api, const Update &update) {
    try {
        api.sendMessage(update.message->chat->id, "Hello world!");
    }
    catch (Telegram::Bot::Types::Error &error) {
        std::cerr << error.what();
    }
}

int main(int argc, char **argv) {

    try {
        Telegram::Bot::Connector handler(argv[1]);//Insert here your token
        handler.onUpdate(sendSomething);
        handler.callback();
    }
    catch (Telegram::Bot::Types::Error &error) {
        std::cerr << error.what();
    }
}