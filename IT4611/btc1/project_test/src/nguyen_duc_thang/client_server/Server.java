package nguyen_duc_thang.client_server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Arrays;


public class Server {
//    public static void main(String[] args) {
//        System.out.println("The Sorter Server is running!");
//        int clientNumber = 0;
//
//        try (ServerSocket listener = new ServerSocket(9898)) {
//            while (true) {
//                // Chấp nhận kết nối từ Client và tạo luồng mới
//                new Sorter(listener.accept(), clientNumber++).start();
//            }
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//    }
//
//    private static class Sorter extends Thread {
//        private Socket socket;
//        private int clientNumber;
//
//        public Sorter(Socket socket, int clientNumber) {
//            this.socket = socket;
//            this.clientNumber = clientNumber;
//            System.out.println("New client #" + clientNumber + " connected at " + socket);
//        }
//
//        public void run() {
//            try {
//                // Khởi tạo luồng đọc và ghi dữ liệu
//                BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
//                PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
//
//                // Gửi thông điệp chào mừng đến Client
//                out.println("Hello, you are client #" + clientNumber);
//
//                // Xử lý dữ liệu từ Client
//                while (true) {
//                    String input = in.readLine();
//                    if (input == null || input.isEmpty()) {
//                        break;
//                    }
//
//                    // Chuyển đổi chuỗi nhập vào thành mảng số nguyên
//                    String[] nums = input.split(" ");
//                    int[] intarr = new int[nums.length];
//                    for (int i = 0; i < nums.length; i++) {
//                        intarr[i] = Integer.parseInt(nums[i]);
//                    }
//
//                    // Sắp xếp mảng số nguyên
//                    NumberSorter sorter = new SelectionSort(); // Có thể thay đổi thuật toán sắp xếp
//                    sorter.sort(intarr);
//
//                    // Chuyển đổi mảng số nguyên thành chuỗi và gửi kết quả về Client
//                    String result = Arrays.toString(intarr);
//                    out.println(result);
//                }
//            } catch (IOException e) {
//                System.out.println("Error handling client #" + clientNumber);
//            } finally {
//                try {
//                    socket.close();
//                } catch (IOException e) {
//                    e.printStackTrace();
//                }
//                System.out.println("Connection with client #" + clientNumber + " closed");
//            }
//        }
//    }
}

