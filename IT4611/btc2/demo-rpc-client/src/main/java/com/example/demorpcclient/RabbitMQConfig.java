package com.example.demorpcclient;

import org.springframework.amqp.core.*;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class RabbitMQConfig {

    @Bean
    public DirectExchange rpcExchange() {
        return new DirectExchange("rpc_exchange");
    }

    @Bean
    public Queue rpcQueue() {
        return new Queue("rpc_queue");
    }

    @Bean
    public Binding binding(DirectExchange exchange, Queue queue) {
        return BindingBuilder.bind(queue)
                .to(exchange)
                .with("rpc");
    }
}