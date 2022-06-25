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
@Table(name = "scope")
@NamedQueries({
        @NamedQuery(name = "Scope.all", query = "select s from Scope s"),
        @NamedQuery(name = "Scope.single", query = "select s from Scope s where s.id = :id")
})
public class Scope {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    private String title;
    private String description;

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


}
