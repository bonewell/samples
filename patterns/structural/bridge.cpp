#include <iostream>
#include <memory>

enum class Type { kFile, kGrab };

enum class Kind { kAudio, kVideo };

class StreamImpl {
    public:
        virtual bool open() = 0;
        virtual void close() = 0;
        virtual Kind kind() = 0;
        virtual ~StreamImpl() = default;
};

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
        explicit Stream(Type type) {
            switch (type) {
                case Type::kFile:
                    impl_ = std::make_unique<FileStream>();
                    break;
                case Type::kGrab:
                    impl_ = std::make_unique<GrabberStream>();
            }
        }

        virtual bool start() {
            return impl_->open();
        }

        virtual void stop() {
            impl_->close();
        }
    protected:
        std::unique_ptr<StreamImpl> impl_;
};

class AudioStream: public Stream {
    public:
        explicit AudioStream(Type type): Stream(type) {}

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
};

class VideoStream: public Stream {
        public:
        explicit VideoStream(Type type): Stream(type) {}

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
};

int main() {
    AudioStream audio(Type::kFile);
    VideoStream video(Type::kGrab);
    std::pair<Stream&, Stream&> stream{audio, video};

    std::cout << std::boolalpha << stream.first.start() << "\n";
    std::cout << std::boolalpha << stream.second.start() << "\n";
}