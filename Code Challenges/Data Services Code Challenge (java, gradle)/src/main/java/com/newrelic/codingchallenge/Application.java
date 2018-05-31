package com.newrelic.codingchallenge;

import java.net.*;
import java.io.*;
import java.util.concurrent.*;
import static java.util.concurrent.TimeUnit.*;

/**
 * Connects to a socket, generates a listener for handling clients, and generates a logger to track global changes.
 * @author Alex Davis
 * @date 4/6/2018
 */

public class Application {

    //The port for receiving data
    private ServerSocket socket = null;

    //Defining the threads to be used and classes to be ran
    private ExecutorService socketHandlerThreadPool;
    private ExecutorService socketListenerThreadPool;
    private ScheduledExecutorService  loggerService;
    private Runnable loggerFunction;

    //Constants
    private final String loggerFileName = "numbers.log";

    //Shared variables
    private ConcurrentHashMap<String, Integer> internalData;
    private FileWriter writer;
    private Object loggingLock;
    private Object shutdown;


    public Application() {
        socketHandlerThreadPool = Executors.newFixedThreadPool(5);
        socketListenerThreadPool = Executors.newFixedThreadPool(1);
        loggerService = Executors.newScheduledThreadPool(1);

        try {
            writer = new FileWriter(loggerFileName, false);
        } catch (IOException exception) {
            exception.printStackTrace();
        }

        internalData = new ConcurrentHashMap();
        internalData.put("recentUniqueCount", 0);
        internalData.put("totalUniqueCount", 0);
        internalData.put("recentDuplicateCount", 0);

        loggingLock = new Object();
        shutdown = new Object();
        loggerFunction = new ApplicationLogger(internalData, loggingLock);

    }


    public void connect(int port) {
        try {
            if (socket == null) {
                socket = new ServerSocket(port);
            }
        } catch(IOException exception) {
            exception.printStackTrace();
        }
    }


    public void run() {
        loggerService.scheduleAtFixedRate(loggerFunction, 1, 10, SECONDS);

        Runnable worker = new ApplicationListener(internalData, writer, loggingLock, socket
                                                    , socketHandlerThreadPool, shutdown);
        socketListenerThreadPool.execute(worker);
        try {
            synchronized (shutdown) {
                shutdown.wait();
            }
            System.out.println("Shutting down");
            socketHandlerThreadPool.shutdown();
            socket.close();
            writer.close();
            socketListenerThreadPool.shutdown();
            loggerService.shutdown();
            return;
        } catch(InterruptedException exception) {
            exception.printStackTrace();
        } catch(IOException exception) {
            exception.printStackTrace();
        }
    }
}
