/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.wba.projectportal.model;

import javax.persistence.*;

/**
 *
 * @author phue
 */
@Entity
@Table(name = "projectscope")
@NamedQueries({
        @NamedQuery(name = "ProjectScope.all", query = "select p from ProjectScope p"),
        @NamedQuery(name = "ProjectScope.single", query = "select p from ProjectScope p where p.id = :id")
})
public class ProjectScope {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    private int projectId;
    private int scopeId;

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

    public int getScopeId() {
        return scopeId;
    }

    public void setScopeId(int scopeId) {
        this.scopeId = scopeId;
    }
}
