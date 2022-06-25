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
@Table(name = "projectartifact")
@NamedQueries({
        @NamedQuery(name = "ProjectArtifact.all", query = "select p from ProjectArtifact p"),
        @NamedQuery(name = "ProjectArtifact.single", query = "select p from ProjectArtifact p where p.id = :id")
})
public class ProjectArtifact {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    private int projectId;
    private int artifactId;
    private Duration actualTime;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getProjectId() {
        return projectId;
    }

    public void setProjectId(int projectId) {
        this.projectId = projectId;
    }

    public int getArtifactId() {
        return artifactId;
    }

    public void setArtifactId(int artifactId) {
        this.artifactId = artifactId;
    }

    public Duration getActualTime() {
        return actualTime;
    }

    public void setActualTime(Duration actualTime) {
        this.actualTime = actualTime;
    }
    
    
}
