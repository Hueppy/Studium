/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.wba.projectportal.model;

import javax.persistence.*;
import java.time.Duration;

/**
 *
 * @author phue
 */
@Entity
@Table(name = "artifact")
@NamedQueries({
        @NamedQuery(name = "Artifact.all", query = "select a from Artifact a"),
        @NamedQuery(name = "Artifact.single", query = "select a from Artifact a where a.id = :id")
})
public class Artifact {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    private String title;
    private String description;
    private int scopeId;
    private Duration plannedTime;
    private Duration actualTime;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public int getScopeId() {
        return scopeId;
    }

    public void setScopeId(int scopeId) {
        this.scopeId = scopeId;
    }

    public Duration getPlannedTime() {
        return plannedTime;
    }

    public void setPlannedTime(Duration plannedTime) {
        this.plannedTime = plannedTime;
    }

    public Duration getActualTime() {
        return actualTime;
    }

    public void setActualTime(Duration actualTime) {
        this.actualTime = actualTime;
    }
}
