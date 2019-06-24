```$xslt
int main(int argc, char** argv){
    if(argc < 2) {
        printf("Please provide a movie file\n");
        return -1;
    }
    try {
        Window window(800, 600);
    
        BlockingQueue queue; // needed for concurrency
    
        av_register_all();  // REALLY IMPORTANT. 
                            // If you do not call this function before initializing Cosumer
                            // your program will crash
        SwsContext ctx(queue, window);
        std::string filename = argv[1];
        Consumer consumer(queue, filename, window);


        window.clear();
        // Draw whatever you want
        window.render();

        consumer.start();
        while (running) {
            
            handleSDLEvent(x, y, running);
            
            window.clear();
            // Draw whatever you want
            window.render();

            ctx.write();  // Reads from the window.render and writes on disk
        }
        
        queue.close() // hey queue when you get empty it means that we finish. 
                      // We are not going to push anything else.
                      
        consumer.join()
        
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
```