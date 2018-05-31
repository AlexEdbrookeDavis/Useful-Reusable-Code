package com.newrelic.codingchallenge;

/**
 * Runs the application.
 * @author Alex Davis
 * @date 4/6/2018
 */

public class Main {

    public static void main(String[] args) {

        System.out.println("Starting up server ....");

        // Add your code here

        Application application = new Application();
        application.connect(4000);
        application.run();
    }
}