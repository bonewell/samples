#include <iostream>
#include <memory>

enum class Kind { kAudio, kVideo };

class StreamImpl {
    public:
        virtual bool open() = 0;
        virtual void close() = 0;
        virtual Kind kind() = 0;
        virtual ~StreamImpl() = default;
};
using StreamImplPtr = std::unique_ptr<StreamImpl>;

class FileStream: public StreamImpl {
    public:
        bool open() override {
            std::cout << "open file\n";
            return true;
        }
        void close() override {
            std::cout << "close file\n";
        }
        Kind kind() override {
            std::cout << "kind audio\n";
            return Kind::kAudio;
        }
};

class GrabberStream: public StreamImpl {
    public:
        bool open() override {
            std::cout << "open device\n";
            return true;
        }
        void close() override {
            std::cout << "close device\n";
        }
        Kind kind() override {
            std::cout << "kind audio\n";
            return Kind::kAudio;
        }
};

class Stream {
    public:
        virtual bool start() = 0;
        virtual void stop() = 0;
        virtual ~Stream() = default;
};

class AudioStream: public Stream {
    public:
        explicit AudioStream(StreamImplPtr stream):
            impl_{std::move(stream)} {}

        bool start() override {
            if (impl_->open()) {
                if (impl_->kind() == Kind::kAudio) {
                    return true;
                } else {
                    impl_->close();
                }
            }
            return false;
        }
    private:
        StreamImplPtr impl_;
};

class VideoStream: public Stream {
    public:
        explicit VideoStream(StreamImplPtr stream):
            impl_{std::move(stream)} {}

        bool start() override {
            if (impl_->open()) {
                if (impl_->kind() == Kind::kVideo) {
                    return true;
                } else {
                    impl_->close();
                }
            }
            return false;
        }
    private:
        StreamImplPtr impl_;
};

int main() {
    AudioStream audio{std::make_unique<FileStream>()};
    VideoStream video{std::make_unique<GrabberStream>()};
    std::pair<Stream&, Stream&> stream{audio, video};

    std::cout << std::boolalpha << stream.first.start() << "\n";
    std::cout << std::boolalpha << stream.second.start() << "\n";
}