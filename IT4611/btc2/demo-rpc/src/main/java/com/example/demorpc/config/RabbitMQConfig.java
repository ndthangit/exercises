package com.example.demorpc.config;

import com.example.demorpc.server.RpcServer;
import org.springframework.amqp.core.Queue;
import org.springframework.amqp.rabbit.connection.ConnectionFactory;
import org.springframework.amqp.rabbit.listener.SimpleMessageListenerContainer;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class RabbitMQConfig {
    public static final String RPC_QUEUE_NAME = "rpc_queue";

    @Bean
    Queue rpcQueue() {
        return new Queue(RPC_QUEUE_NAME);
    }

    // Cấu hình cho Server
    @Bean
    SimpleMessageListenerContainer serverContainer(ConnectionFactory connectionFactory, RpcServer rpcServer) {
        SimpleMessageListenerContainer container = new SimpleMessageListenerContainer();
        container.setConnectionFactory(connectionFactory);
        container.setQueueNames(RPC_QUEUE_NAME);
        container.setMessageListener(rpcServer);
        return container;
    }
}