package com.example.demorpc.server;

import org.springframework.amqp.core.Message;
import org.springframework.amqp.core.MessageProperties;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.amqp.rabbit.listener.api.ChannelAwareMessageListener;
import org.springframework.stereotype.Component;
import com.rabbitmq.client.Channel;

@Component
public class RpcServer implements ChannelAwareMessageListener {

    private final RabbitTemplate rabbitTemplate;

    public RpcServer(RabbitTemplate rabbitTemplate) {
        this.rabbitTemplate = rabbitTemplate;
    }

    private int fib(int n) {
        if (n <= 0) return 0;
        if (n == 1) return 1;
        return fib(n - 1) + fib(n - 2);
    }

    @Override
    public void onMessage(Message message, Channel channel) throws Exception {
        String request = new String(message.getBody());
        String replyTo = message.getMessageProperties().getReplyTo();
        String corrId = message.getMessageProperties().getCorrelationId();

        System.out.println(" [Server] Received request for fib(" + request + ")");

        String response;
        try {
            int n = Integer.parseInt(request);
            response = String.valueOf(fib(n));
        } catch (NumberFormatException e) {
            response = "Error: Invalid input";
        }

        // Gửi phản hồi
        MessageProperties props = new MessageProperties();
        props.setCorrelationId(corrId);
        Message reply = new Message(response.getBytes(), props);
        rabbitTemplate.send(replyTo, reply);

        channel.basicAck(message.getMessageProperties().getDeliveryTag(), false);
    }
}
