#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

class ISubscriber {
public:
    virtual void update() = 0;
    virtual ~ISubscriber() {}
};

class IChannel {
public:
    virtual void subscribe(ISubscriber* subsriber) = 0;
    virtual void unsubscribe(ISubscriber* subsriber) = 0;
    virtual void notifySubscribers() = 0;

    virtual ~IChannel() {}
};

class Channel : public IChannel {
private:
    vector<ISubscriber*> subscribers;
    string name;
    string latestVideo;
public:
    Channel(const string& name) {
        this->name = name;
    }

    void subscribe(ISubscriber* subsriber) override {
        if(find(subscribers.begin(), subscribers.end(), subsriber) == subscribers.end()) {
            subscribers.push_back(subsriber);
        }
    }

    void unsubscribe(ISubscriber* subsriber) override {
        auto it = find(subscribers.begin(), subscribers.end(), subsriber);
        if(it != subscribers.end()) {
            subscribers.erase(it);
        }
    }

    void notifySubscribers() override {
        for(ISubscriber* s : subscribers) {
            s->update();
        }
    }

    // upload a video and notify all subscribers
    void uploadVideo(const string& title) {
        latestVideo = title;
        cout << "\nUploaded video " << title << endl;
        notifySubscribers();
    }

    string getVideoData() {
        return "\nCheckout our new video " + latestVideo + "\n";
    }
};

class Subscriber : public ISubscriber {
private:
    string name;
    Channel* ch;

public:
    Subscriber(const string& name, Channel* ch) {
        this->name = name;
        this->ch = ch;
    }

    void update() override {
        cout << "Hey " << name << ch->getVideoData() << endl;
    }


};

int main() {
    Channel* channel = new Channel("SandBox");

    Subscriber* subs1 = new Subscriber("Alex", channel);
    Subscriber* subs2 = new Subscriber("Emma", channel);

    channel->subscribe(subs1);
    channel->subscribe(subs2);

    channel->uploadVideo("Observer Pattern Design");
    
    channel->unsubscribe(subs2);

    channel->uploadVideo("Here Comes the Money");

    return 0;
}