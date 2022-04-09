package com.fsradar.api.dto;

import com.fsradar.api.constants.AircraftModel;

public class Aircraft {
    private AircraftModel model;
    private Telemetry telemetry;
    private Boolean isGearDown;
    private Boolean isOnGround;

    public AircraftModel getModel() {
        return model;
    }

    public void setModel(AircraftModel model) {
        this.model = model;
    }

    public Telemetry getTelemetry() {
        return telemetry;
    }

    public void setTelemetry(Telemetry telemetry) {
        this.telemetry = telemetry;
    }

    public Boolean getGearDown() {
        return isGearDown;
    }

    public void setGearDown(Boolean gearDown) {
        isGearDown = gearDown;
    }

    public Boolean getOnGround() {
        return isOnGround;
    }

    public void setOnGround(Boolean onGround) {
        isOnGround = onGround;
    }

    @Override
    public String toString() {
        return "Aircraft{" +
                "model=" + model +
                ", telemetry=" + telemetry +
                ", isGearDown=" + isGearDown +
                ", isOnGround=" + isOnGround +
                '}';
    }
}
