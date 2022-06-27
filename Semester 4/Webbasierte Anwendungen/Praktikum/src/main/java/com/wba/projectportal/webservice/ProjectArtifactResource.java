package com.wba.projectportal.webservice;

import com.wba.projectportal.model.Project;
import com.wba.projectportal.model.ProjectArtifact;

import javax.annotation.Resource;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.TypedQuery;
import javax.transaction.UserTransaction;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import java.net.URI;
import java.time.Duration;
import java.time.temporal.ChronoUnit;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

@Path("/projectartifact")
public class ProjectArtifactResource {
    @PersistenceContext(unitName = "default")
    private EntityManager em;

    @Resource
    private UserTransaction utx;

    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public Response all() {
        List<ProjectArtifact> projectArtifacts = em.createNamedQuery("ProjectArtifact.all", ProjectArtifact.class).getResultList();
        Response.ResponseBuilder rb = Response.ok();
        rb.entity(projectArtifacts);

        return rb.build();
    }

    @GET
    @Path("{id}")
    @Produces(MediaType.APPLICATION_JSON)
    public Response single(@PathParam("id") int id) {
        Response.ResponseBuilder rb;

        try {
            TypedQuery<ProjectArtifact> query = em.createNamedQuery("ProjectArtifact.single", ProjectArtifact.class);
            query.setParameter("id", id);
            List<ProjectArtifact> p = query.getResultList();

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
    public Response create(ProjectArtifact projectArtifact) {
        Response.ResponseBuilder rb;

        try {
            this.utx.begin();
            this.em.persist(projectArtifact);
            this.utx.commit();
            rb = Response.created(URI.create(Integer.toString(projectArtifact.getId())));
        } catch (Exception e) {
            rb = Response.serverError();
            rb.entity(e);
        }

        return rb.build();
    }

    @PUT
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
    public Response update(ProjectArtifact projectArtifact) {
        Response.ResponseBuilder rb;

        try {
            this.utx.begin();
            em.merge(projectArtifact);
            this.utx.commit();

            rb = Response.ok();
        } catch (Exception e) {
            rb = Response.serverError();
            rb.entity(e.toString());
        }

        return rb.build();
    }
}
