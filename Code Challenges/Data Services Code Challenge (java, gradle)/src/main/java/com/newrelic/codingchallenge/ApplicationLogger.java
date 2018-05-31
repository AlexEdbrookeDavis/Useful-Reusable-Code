package com.newrelic.codingchallenge;

import java.util.concurrent.ConcurrentHashMap;

/**
 * Reads internal log populated by Client Handlers, and prints information to standard out every 10 seconds.
 * @author Alex Davis
 * @date 4/6/2018
 */
public class ApplicationLogger implements Runnable {
    private Object loggingLock;

    private ConcurrentHashMap internalDataLog;

    ApplicationLogger(ConcurrentHashMap internalDataLog, Object loggingLock) {
        this.internalDataLog = internalDataLog;
        this.loggingLock = loggingLock;
    }

    public void run() {
        synchronized (loggingLock) {
            System.out.println("Received " + internalDataLog.get("recentUniqueCount")
                    + " unique numbers, " + internalDataLog.get("recentDuplicateCount")
                    + " duplicates. Unique total: " + internalDataLog.get("totalUniqueCount"));
            internalDataLog.put("recentUniqueCount", 0);
            internalDataLog.put("recentDuplicateCount", 0);
        }
    }
}
