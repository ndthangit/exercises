package com.example.demorpcserver;
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.amqp.core.Message;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.stereotype.Component;

@Component
public class RPCServer {

    private final RabbitTemplate rabbitTemplate;

    public RPCServer(RabbitTemplate rabbitTemplate) {
        this.rabbitTemplate = rabbitTemplate;
    }

    private static int fib(int n) {
        if (n <= 0) return 0;
        if (n == 1) return 1;
        return fib(n - 1) + fib(n - 2);
    }

    @RabbitListener(queues = "rpc_queue")
    public void processRpcRequest(Message request) {
        try {
            String message = new String(request.getBody());
            int n = Integer.parseInt(message);
            System.out.println(" [.] Processing fib(" + n + ")");

            String response = String.valueOf(fib(n));

            // Thêm delay 2 giây
            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                System.out.println(" [x] Processing interrupted");
                return;
            }

            // Gửi phản hồi
            rabbitTemplate.convertAndSend(
                    request.getMessageProperties().getReplyTo(),
                    response,
                    m -> {
                        m.getMessageProperties().setCorrelationId(
                                request.getMessageProperties().getCorrelationId()
                        );
                        return m;
                    }
            );
        } catch (Exception e) {
            System.out.println(" [x] Error: " + e.getMessage());
        }
    }
}