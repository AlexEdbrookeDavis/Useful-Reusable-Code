package com.newrelic.codingchallenge;

import com.sun.xml.internal.ws.policy.privateutil.PolicyUtils;

import java.net.*;
import java.io.*;
import java.util.Random;

/**
 * Created by Zosit on 4/5/2018.
 */
public class ClientTester extends Thread {
    private int number;
    private Random rand = new Random();

    public ClientTester(int num) {
        number = num;
    }

    public void run() {
        try {
            String serverName = "localHost";
            int port = 4000;
            System.out.println("Making Connection to " + serverName + ", port " + port);
            Socket client = new Socket(serverName, port);

            System.out.println("Connected to " + client.getRemoteSocketAddress());
            OutputStream outToServer = client.getOutputStream();
            ObjectOutputStream out = new ObjectOutputStream(new BufferedOutputStream(outToServer));

            for(long i = 0; i < 4000000; i++) {
                out.writeUTF(String.format("%09d" + String.format("%n"), i));
            }

            out.close();

        } catch (IOException e) {
            System.out.println("IOException!");
        }
    }

    public void run2() {
        try {
            String serverName = "localHost";
            int port = 4000;
            System.out.println("Making Connection to " + serverName + ", port " + port);
            Socket client = new Socket(serverName, port);

            System.out.println("Connected to " + client.getRemoteSocketAddress());
            OutputStream outToServer = client.getOutputStream();
            ObjectOutputStream out = new ObjectOutputStream(new BufferedOutputStream(outToServer));

            for(long i = 4000000; i > 0; i--) {
                out.writeUTF(String.format("%09d" + String.format("%n"), i));
            }

            out.close();

        } catch (IOException e) {
            System.out.println("IOException!");
        }
    }

    public void run3() {
        try {
            String serverName = "localHost";
            int port = 4000;
            System.out.println("Making Connection to " + serverName + ", port " + port);
            Socket client = new Socket(serverName, port);

            System.out.println("Connected to " + client.getRemoteSocketAddress());
            OutputStream outToServer = client.getOutputStream();
            ObjectOutputStream out = new ObjectOutputStream(new BufferedOutputStream(outToServer));

            for(long i = 0; i < 4000000; i++) {
                out.writeUTF(String.format("%09d" + String.format("%n"), rand.nextInt(999999999)));
            }

            out.close();

        } catch (IOException e) {
            System.out.println("IOException!");
        }
    }
    public void run4() {
        try {
            String serverName = "localHost";
            int port = 4000;
            System.out.println("Making Connection to " + serverName + ", port " + port);
            Socket client = new Socket(serverName, port);

            System.out.println("Connected to " + client.getRemoteSocketAddress());
            OutputStream outToServer = client.getOutputStream();
            ObjectOutputStream out = new ObjectOutputStream(new BufferedOutputStream(outToServer));

            for (long i = 0; i < 4000000; i++) {
                out.writeUTF(String.format("INVALID INPUT" + String.format("%n")));
            }

            out.close();

        } catch (IOException e) {
            System.out.println("IOException!");
        }
    }

    public void run5() {
        try {
            String serverName = "localHost";
            int port = 4000;
            System.out.println("Making Connection to " + serverName + ", port " + port);
            Socket client = new Socket(serverName, port);

            System.out.println("Connected to " + client.getRemoteSocketAddress());
            OutputStream outToServer = client.getOutputStream();
            ObjectOutputStream out = new ObjectOutputStream(new BufferedOutputStream(outToServer));

            out.writeUTF("terminate" + String.format("%n"));


            out.close();

        } catch (IOException e) {
            System.out.println("IOException!");
        }
    }
}
