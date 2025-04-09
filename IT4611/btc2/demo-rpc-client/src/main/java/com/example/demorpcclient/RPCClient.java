package com.example.demorpcclient;

import org.springframework.amqp.core.DirectExchange;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

@Component
public class RPCClient {

    private final RabbitTemplate rabbitTemplate;
    private final DirectExchange directExchange;

    @Autowired
    public RPCClient(RabbitTemplate rabbitTemplate, DirectExchange directExchange) {
        this.rabbitTemplate = rabbitTemplate;
        this.directExchange = directExchange;
    }

    public String call(String message) {
        // Gửi message và chờ phản hồi
        return (String) rabbitTemplate.convertSendAndReceive(
                directExchange.getName(),
                "rpc",
                message
        );
    }
}
