package com.newrelic.codingchallenge;

import org.junit.Test;

public class MainTest {

    @Test
    public void test() {

        // Test something here (optional)
        System.out.println("Testing");
    }

    @Test
    public void testConnection() throws Exception {

        // Test something here (optional)
        ClientTester clientTester = new ClientTester(1);

        //server.connect(4000);
        //server.listen();
        clientTester.run();

    }

    @Test
    public void testConnection2() throws Exception {

        // Test something here (optional)
        ClientTester clientTester = new ClientTester(2);
        clientTester.run2();
    }
    @Test
    public void testConnection3() throws Exception {

        // Test something here (optional)
        ClientTester clientTester = new ClientTester(3);
        clientTester.run3();
    }
    @Test
    public void testConnection4() throws Exception {

        // Test something here (optional)
        ClientTester clientTester = new ClientTester(4);
        clientTester.run4();
    }
    @Test
    public void testConnection5() throws Exception {

        // Test something here (optional)
        ClientTester clientTester = new ClientTester(5);
        clientTester.run5();
    }
    @Test
    public void testConnection6() throws Exception {

        // Test something here (optional)
        ClientTester clientTester = new ClientTester(6);
        clientTester.run();
    }
}