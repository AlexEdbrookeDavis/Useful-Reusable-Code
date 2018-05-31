package com.newrelic.codingchallenge;
import java.io.*;
import java.util.concurrent.ConcurrentHashMap;


/**
 * Listens to clients inputs, shutting down on invalid inputs, logging all valid number inputs appropriately,
 * and shutting down on "terminate" input.
 * @author Alex Davis
 * @date 4/6/2018
 */

public class ApplicationClientHandlerThread implements Runnable {
    //The unique input stream for the client
    private ObjectInputStream in;

    //Logging text file target and internal logging data
    private FileWriter writer;
    private ConcurrentHashMap<String, Integer> internalData;

    //lock for handling hashmap data
    private Object loggingLock;
    private Object shutdown;


    public ApplicationClientHandlerThread(ObjectInputStream inputSocket, ConcurrentHashMap internalData
            , FileWriter writer, Object loggingLock, Object shutdown) {
        this.in = inputSocket;
        this.internalData = internalData;
        this.writer = writer;
        this.loggingLock = loggingLock;
        this.shutdown = shutdown;
    }


    public void run() {
        while (true && !Thread.currentThread().isInterrupted()) {
            try {
                String input = in.readUTF();

                if(input.matches("terminate" + String.format("%n"))) {
                    in.close();
                    synchronized (shutdown) {
                        shutdown.notify();
                    }
                    return;
                } else if(input.matches("^[0-9]{9}" + String.format("%n"))) {
                    if(internalData.get(input) == null) {
                        synchronized (loggingLock) {
                            internalData.put(input, 1);
                            internalData.put("recentUniqueCount", internalData.get("recentUniqueCount") + 1);
                            internalData.put("totalUniqueCount", internalData.get("totalUniqueCount") + 1);
                        }
                        synchronized (writer) {
                            writer.write(input);
                        }

                    } else {
                        synchronized (loggingLock) {
                            internalData.put("recentDuplicateCount", internalData.get("recentDuplicateCount") + 1);
                        }
                    }
                } else {
                    in.close();
                    return;
                }
            } catch (IOException e) {
                try {
                    writer.close();
                } catch (IOException exception) {
                    exception.printStackTrace();
                }
                break;
            }
        }
        try {
            in.close();
            return;
        } catch (IOException exception){
            exception.printStackTrace();
        }
    }
}
