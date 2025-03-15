package nguyen_duc_thang.client_server;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        try (Socket socket = new Socket("127.0.0.1", 80)) {
            // Khởi tạo luồng đọc và ghi dữ liệu
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

            // Đọc thông điệp chào mừng từ Server
            System.out.println(in.readLine());

            // Khởi tạo Scanner để nhập dữ liệu từ người dùng
            Scanner scanner = new Scanner(System.in);
            while (true) {
                System.out.print("Enter numbers separated by spaces (or press Enter to exit): ");
                String message = scanner.nextLine();
                if (message.isEmpty()) {
                    break;
                }
                out.println(message);
                String response = in.readLine();
                System.out.println("Sorted numbers: " + response);
            }
            // Đóng kết nối
            scanner.close();
            System.out.println("Client disconnected.");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}