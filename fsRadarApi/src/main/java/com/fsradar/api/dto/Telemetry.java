package com.fsradar.api.dto;

public class Telemetry {
    private Double latitude;
    private Double longitude;
    private Double altitude;
    private Double pitch;
    private Double bank;
    private Double trueHeading;
    private Double magneticHeading;

    public Double getLatitude() {
        return latitude;
    }

    public void setLatitude(Double latitude) {
        this.latitude = latitude;
    }

    public Double getLongitude() {
        return longitude;
    }

    public void setLongitude(Double longitude) {
        this.longitude = longitude;
    }

    public Double getAltitude() {
        return altitude;
    }

    public void setAltitude(Double altitude) {
        this.altitude = altitude;
    }

    public Double getPitch() {
        return pitch;
    }

    public void setPitch(Double pitch) {
        this.pitch = pitch;
    }

    public Double getBank() {
        return bank;
    }

    public void setBank(Double bank) {
        this.bank = bank;
    }

    public Double getTrueHeading() {
        return trueHeading;
    }

    public void setTrueHeading(Double trueHeading) {
        this.trueHeading = trueHeading;
    }

    public Double getMagneticHeading() {
        return magneticHeading;
    }

    public void setMagneticHeading(Double magneticHeading) {
        this.magneticHeading = magneticHeading;
    }

    @Override
    public String toString() {
        return "Telemetry{" +
                "latitude=" + latitude +
                ", longitude=" + longitude +
                ", altitude=" + altitude +
                ", pitch=" + pitch +
                ", bank=" + bank +
                ", trueHeading=" + trueHeading +
                ", magneticHeading=" + magneticHeading +
                '}';
    }
}
