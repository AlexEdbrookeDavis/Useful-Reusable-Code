package com.newrelic.codingchallenge;

import java.io.FileWriter;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.ThreadPoolExecutor;

/**
 * Listens for clients and generates threads to communicate with each. Max 5 clients
 * @author Alex Davis
 * @date 4/6/2018
 */

public class ApplicationListener implements Runnable {

    //The port for receiving data
    private ServerSocket socket;

    //Shared variables
    private ConcurrentHashMap<String, Integer> internalData;
    private FileWriter writer;
    private Object loggingLock;
    private Object shutdown;

    //Client handler thread pool
    private ExecutorService socketHandlerThreadPool;


    public ApplicationListener(ConcurrentHashMap<String, Integer> internalData, FileWriter writer
                                , Object loggingLock, ServerSocket socket, ExecutorService socketHandlerThreadPool
                                , Object shutdown) {
        this.internalData = internalData;
        this.writer = writer;
        this.loggingLock = loggingLock;
        this.socket = socket;
        this.socketHandlerThreadPool = socketHandlerThreadPool;
        this.shutdown = shutdown;
    }


    public void run() {
        try {
            while (true) {
                Socket server = socket.accept();
                if (((ThreadPoolExecutor) socketHandlerThreadPool).getActiveCount() < 5) {
                    Runnable worker = new ApplicationClientHandlerThread(new ObjectInputStream(server.getInputStream())
                                                                            , internalData, writer, loggingLock, shutdown);
                    socketHandlerThreadPool.execute(worker);
                } else {
                    server.close();
                }
            }
        } catch(IOException exception) {
            //Socket must be closed to escape the Socket accept
        }
    }
}
