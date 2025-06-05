package com.example.demorpcclient;

import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ConfigurableApplicationContext;

@SpringBootApplication
public class DemoRpcClientApplication {

    public static void main(String[] args) {
        ConfigurableApplicationContext ctx = SpringApplication.run(DemoRpcClientApplication.class, args);
        RabbitTemplate rabbitTemplate = ctx.getBean(RabbitTemplate.class);

        try {
            for (int i = 0; i < 32; i++) {
                String i_str = Integer.toString(i);
                System.out.println(" [x] Requesting fib(" + i_str + ")");

                // Gửi và nhận message qua RabbitTemplate
                String response = (String) rabbitTemplate.convertSendAndReceive(
                        "rpc_exchange",  // Tên exchange
                        "rpc",           // Routing key
                        i_str            // Message content
                );

                System.out.println(" [.] Got '" + response + "'");
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            ctx.close();
        }
    }

}
