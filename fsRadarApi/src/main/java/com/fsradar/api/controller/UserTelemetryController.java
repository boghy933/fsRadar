package com.fsradar.api.controller;

import com.fsradar.api.dto.Aircraft;
import com.fsradar.api.dto.Telemetry;
import com.fsradar.api.service.KafkaService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("user")
public class UserTelemetryController {

    @Autowired
    KafkaService kafkaService;

    @PostMapping("telemetry")
    public Aircraft telemetry(@RequestBody Aircraft aircraft) {
        kafkaService.sendMessage(aircraft);
        return aircraft;
    }
}
