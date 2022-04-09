package com.fsradar.api.service;

import com.fsradar.api.dto.Aircraft;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.kafka.core.KafkaTemplate;
import org.springframework.stereotype.Service;

@Service
public class KafkaService {
    @Autowired
    private KafkaTemplate<String, Aircraft> kafkaTemplate;

    public void sendMessage(Aircraft aircraft) {
        kafkaTemplate.send("aircraftTelemetry", aircraft);
    }

    @KafkaListener(topics = "aircraftTelemetry", groupId = "foo")
    public void listenGroupFoo(Aircraft message) {
        System.out.println("Received Message in group foo: " + message);
    }
}
