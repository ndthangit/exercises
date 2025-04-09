package com.example.demorpc.controller;

import org.springframework.amqp.core.Message;
import org.springframework.amqp.core.MessageProperties;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;
import java.nio.charset.StandardCharsets;
import java.util.UUID;

@RestController
public class RpcClientController {
    private final RabbitTemplate rabbitTemplate;

    public RpcClientController(RabbitTemplate rabbitTemplate) {
        this.rabbitTemplate = rabbitTemplate;
    }

    @GetMapping("/fib/{n}")
    public String callFib(@PathVariable int n) {
        String queueName = "rpc_queue";
        String replyQueueName = rabbitTemplate.execute(channel -> {
            return channel.queueDeclare().getQueue();
        });

        MessageProperties props = new MessageProperties();
        props.setReplyTo(replyQueueName);
        props.setCorrelationId(UUID.randomUUID().toString());

        Message request = new Message(
                String.valueOf(n).getBytes(StandardCharsets.UTF_8),
                props
        );

        System.out.println(" [Client] Sending request for fib(" + n + ")");
        Message response = rabbitTemplate.sendAndReceive(queueName, request);

        if (response != null) {
            return new String(response.getBody(), StandardCharsets.UTF_8);
        } else {
            return "No response from server";
        }
    }
}