package com.wba.projectportal.webservice;

import com.wba.projectportal.model.Project;

import javax.annotation.Resource;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.Query;
import javax.persistence.TypedQuery;
import javax.transaction.*;
import javax.transaction.NotSupportedException;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import java.net.URI;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.logging.Level;

@Path("/project")
public class ProjectResource {
    @PersistenceContext(unitName = "default")
    private EntityManager em;

    @Resource
    private UserTransaction utx;

    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public Response all() {
        List<Project> projects = em.createNamedQuery("Project.all", Project.class).getResultList();
        Response.ResponseBuilder rb = Response.ok();
        rb.entity(projects);

        return rb.build();
    }

    @GET
    @Path("{id}")
    @Produces(MediaType.APPLICATION_JSON)
    public Response single(@PathParam("id") int id) {
        Response.ResponseBuilder rb;

        try {
            TypedQuery<Project> query = em.createNamedQuery("Project.single", Project.class);
            query.setParameter("id", id);
            Project p = query.getSingleResult();

            rb = Response.ok();
            rb.entity(p);
        } catch (Exception e) {
            rb = Response.status(Response.Status.NOT_FOUND);
        }

        return rb.build();
    }

    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
    public Response create(Project project) {
        Response.ResponseBuilder rb;

        try {
            this.utx.begin();
            this.em.persist(project);
            this.utx.commit();
            rb = Response.created(URI.create(Integer.toString(project.getId())));
        } catch (Exception e) {
            rb = Response.serverError();
            rb.entity(e);
        }

        return rb.build();
    }

    @PUT
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
    public Response update(Project project) {
        Response.ResponseBuilder rb;

        try {
            this.utx.begin();
            em.merge(project);
            this.utx.commit();

            rb = Response.ok();
        } catch (Exception e) {
            rb = Response.serverError();
            rb.entity(e.toString());
        }

        return rb.build();
    }
}