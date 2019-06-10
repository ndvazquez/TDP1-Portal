```$xslt
int main(int argc, char** argv){
    if(argc < 2) {
        printf("Please provide a movie file\n");
        return -1;
    }
    try {
        av_register_all();  // REALLY IMPORTANT. 
                            // If you do not call this function before initializing SwsContext
                            // your program will crash
        std::string outputFilename = argv[1];
        SwsContext ctx(outputFilename);


        Window window(800, 600);
        window.clear();
        // Draw whatever you want
        window.render()

        while (running) {
            
            handleSDLEvent(x, y, running);
            
            window.clear();
            // Draw whatever you want
            window.render()

            ctx.write(window);  // Reads from the window.render and writes on disk
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
```