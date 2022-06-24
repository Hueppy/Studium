using System;
using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata;
using FHGuide.Shared.Models;

namespace FHGuide.Shared.Contexts
{
    public partial class FHGuideContext : DbContext
    {
        public FHGuideContext()
        {
        }

        public FHGuideContext(DbContextOptions<FHGuideContext> options)
            : base(options)
        {
        }

        public virtual DbSet<Account> Accounts { get; set; } = null!;
        public virtual DbSet<Appointment> Appointments { get; set; } = null!;
        public virtual DbSet<Course> Courses { get; set; } = null!;
        public virtual DbSet<Faq> Faqs { get; set; } = null!;
        public virtual DbSet<Module> Modules { get; set; } = null!;
        public virtual DbSet<Rating> Ratings { get; set; } = null!;
        public virtual DbSet<RatingValue> Ratingvalues { get; set; } = null!;
        public virtual DbSet<RoadmapItem> Roadmapitems { get; set; } = null!;
        public virtual DbSet<Schedule> Schedules { get; set; } = null!;
        public virtual DbSet<ScheduleCourse> ScheduleCourses { get; set; } = null!;
        public virtual DbSet<Zoom> Zooms { get; set; } = null!;

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            if (!optionsBuilder.IsConfigured)
            {
                var server = Environment.GetEnvironmentVariable("DB_SERVER") ?? "localhost";
                var user = Environment.GetEnvironmentVariable("DB_USER") ?? "root";
                var password = Environment.GetEnvironmentVariable("DB_PASSWORD") ?? "example";
                var database = Environment.GetEnvironmentVariable("DB_DATABASE") ?? "fhguide";
            
                optionsBuilder.UseMySql($"server={server};user={user};password={password};database={database}", Microsoft.EntityFrameworkCore.ServerVersion.Parse("10.6.5-mariadb"));
            }
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.UseCollation("utf8mb4_general_ci")
                .HasCharSet("utf8mb4");

            modelBuilder.Entity<Account>(entity =>
            {
                entity.ToTable("account");

                entity.Property(e => e.AccountId)
                    .HasColumnType("int(11)")
                    .HasColumnName("accountID");

                entity.Property(e => e.CreateDate).HasColumnName("createdate");

                entity.Property(e => e.Email)
                    .HasMaxLength(50)
                    .HasColumnName("email");

                entity.Property(e => e.Password)
                    .HasMaxLength(100)
                    .HasColumnName("password");

                entity.Property(e => e.Username)
                    .HasMaxLength(16)
                    .HasColumnName("username");
            });

            modelBuilder.Entity<Appointment>(entity =>
            {
                entity.ToTable("appointment");

                entity.HasIndex(e => e.CourseId, "course_appointment_idx");

                entity.Property(e => e.Appointmentid)
                    .HasColumnType("int(11)")
                    .HasColumnName("appointmentid");

                entity.Property(e => e.CourseId)
                    .HasColumnType("int(11)")
                    .HasColumnName("courseID");

                entity.Property(e => e.Day)
                    .HasMaxLength(10)
                    .HasColumnName("day");

                entity.Property(e => e.End)
                    .HasMaxLength(10)
                    .HasColumnName("end");

                entity.Property(e => e.Start)
                    .HasMaxLength(10)
                    .HasColumnName("start");

                entity.HasOne(d => d.Course)
                    .WithMany(p => p.Appointments)
                    .HasForeignKey(d => d.CourseId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("course_appointment");
            });

            modelBuilder.Entity<Course>(entity =>
            {
                entity.ToTable("course");

                entity.HasIndex(e => e.ModuleId, "module_course_idx");

                entity.HasIndex(e => e.ZoomId, "zoom_course_idx");

                entity.Property(e => e.CourseId)
                    .HasColumnType("int(11)")
                    .HasColumnName("courseID");

                entity.Property(e => e.Description)
                    .HasMaxLength(200)
                    .HasColumnName("description");

                entity.Property(e => e.ModuleId)
                    .HasColumnType("int(11)")
                    .HasColumnName("moduleID");

                entity.Property(e => e.Name)
                    .HasMaxLength(25)
                    .HasColumnName("name");

                entity.Property(e => e.Room)
                    .HasMaxLength(10)
                    .HasColumnName("room");

                entity.Property(e => e.ZoomId)
                    .HasColumnType("int(11)")
                    .HasColumnName("zoomID");

                entity.HasOne(d => d.Module)
                    .WithMany(p => p.Courses)
                    .HasForeignKey(d => d.ModuleId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("module_course");

                entity.HasOne(d => d.Zoom)
                    .WithMany(p => p.Courses)
                    .HasForeignKey(d => d.ZoomId)
                    .HasConstraintName("zoom_course");
            });

            modelBuilder.Entity<Faq>(entity =>
            {
                entity.ToTable("faq");

                entity.HasIndex(e => e.AccountId, "account_faq_idx");

                entity.HasIndex(e => e.ModuleId, "module_faq_idx");

                entity.Property(e => e.FaqId)
                    .HasColumnType("int(11)")
                    .HasColumnName("faqID");

                entity.Property(e => e.AccountId)
                    .HasColumnType("int(11)")
                    .HasColumnName("accountID");

                entity.Property(e => e.Answer)
                    .HasMaxLength(200)
                    .HasColumnName("answer");

                entity.Property(e => e.Categorie)
                    .HasMaxLength(25)
                    .HasColumnName("categorie");

                entity.Property(e => e.ModuleId)
                    .HasColumnType("int(11)")
                    .HasColumnName("moduleID");

                entity.Property(e => e.Question)
                    .HasMaxLength(200)
                    .HasColumnName("question");

                entity.HasOne(d => d.Account)
                    .WithMany(p => p.Faqs)
                    .HasForeignKey(d => d.AccountId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("account_faq");

                entity.HasOne(d => d.Module)
                    .WithMany(p => p.Faqs)
                    .HasForeignKey(d => d.ModuleId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("module_faq");
            });

            modelBuilder.Entity<Module>(entity =>
            {
                entity.ToTable("module");

                entity.Property(e => e.ModuleId)
                    .HasColumnType("int(11)")
                    .HasColumnName("moduleID");

                entity.Property(e => e.Active)
                    .HasColumnType("tinyint(4)")
                    .HasColumnName("active");

                entity.Property(e => e.Dependencies)
                    .HasMaxLength(500)
                    .HasColumnName("dependencies");

                entity.Property(e => e.Description)
                    .HasMaxLength(200)
                    .HasColumnName("description");

                entity.Property(e => e.Name)
                    .HasMaxLength(30)
                    .HasColumnName("name");

                entity.Property(e => e.Tags)
                    .HasMaxLength(500)
                    .HasColumnName("tags");
            });

            modelBuilder.Entity<Rating>(entity =>
            {
                entity.ToTable("rating");

                entity.HasIndex(e => e.AccountId, "account_rating_idx");

                entity.HasIndex(e => e.ModuleId, "module_rating_idx");

                entity.Property(e => e.RatingId)
                    .HasColumnType("int(11)")
                    .HasColumnName("ratingID");

                entity.Property(e => e.AccountId)
                    .HasColumnType("int(11)")
                    .HasColumnName("accountID");

                entity.Property(e => e.Description)
                    .HasMaxLength(200)
                    .HasColumnName("description");

                entity.Property(e => e.ModuleId)
                    .HasColumnType("int(11)")
                    .HasColumnName("moduleID");

                entity.HasOne(d => d.Account)
                    .WithMany(p => p.Ratings)
                    .HasForeignKey(d => d.AccountId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("account_rating");

                entity.HasOne(d => d.Module)
                    .WithMany(p => p.Ratings)
                    .HasForeignKey(d => d.ModuleId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("module_rating");
            });

            modelBuilder.Entity<RatingValue>(entity =>
            {
                entity.ToTable("ratingvalue");

                entity.HasIndex(e => e.RatingId, "rating_ratingvalue_idx");

                entity.Property(e => e.RatingValueId)
                    .HasColumnType("int(11)")
                    .HasColumnName("ratingvalueID");

                entity.Property(e => e.Categorie)
                    .HasMaxLength(25)
                    .HasColumnName("categorie");

                entity.Property(e => e.RatingId)
                    .HasColumnType("int(11)")
                    .HasColumnName("ratingid");

                entity.Property(e => e.Text)
                    .HasMaxLength(45)
                    .HasColumnName("ratingvaluecol");

                entity.Property(e => e.Value)
                    .HasColumnType("int(11)")
                    .HasColumnName("value");

                entity.HasOne(d => d.Rating)
                    .WithMany(p => p.RatingValues)
                    .HasForeignKey(d => d.RatingId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("rating_ratingvalue");
            });

            modelBuilder.Entity<RoadmapItem>(entity =>
            {
                entity.ToTable("roadmapitems");

                entity.HasIndex(e => e.CourseId, "course_roadmapitems_idx");

                entity.Property(e => e.RoadmapItemId)
                    .HasColumnType("int(11)")
                    .HasColumnName("roadmapitemid");

                entity.Property(e => e.CourseId)
                    .HasColumnType("int(11)")
                    .HasColumnName("courseID");

                entity.Property(e => e.Material)
                    .HasMaxLength(50)
                    .HasColumnName("material");

                entity.Property(e => e.Name)
                    .HasMaxLength(30)
                    .HasColumnName("name");

                entity.Property(e => e.Style)
                    .HasMaxLength(10)
                    .HasColumnName("style");

                entity.Property(e => e.Week)
                    .HasMaxLength(5)
                    .HasColumnName("week");

                entity.HasOne(d => d.Course)
                    .WithMany(p => p.RoadmapItems)
                    .HasForeignKey(d => d.CourseId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("course_roadmapitems");
            });

            modelBuilder.Entity<Schedule>(entity =>
            {
                entity.ToTable("schedule");

                entity.HasIndex(e => e.AccountId, "account_schedule_idx");

                entity.Property(e => e.ScheduleId)
                    .HasColumnType("int(11)")
                    .HasColumnName("scheduleID");

                entity.Property(e => e.AccountId)
                    .HasColumnType("int(11)")
                    .HasColumnName("accountID");

                entity.Property(e => e.CreateDate).HasColumnName("createdate");

                entity.Property(e => e.ExpireDate).HasColumnName("expiredate");

                entity.HasOne(d => d.Account)
                    .WithMany(p => p.Schedules)
                    .HasForeignKey(d => d.AccountId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("account_schedule");
            });

            modelBuilder.Entity<ScheduleCourse>(entity =>
            {
                entity.HasNoKey();

                entity.ToTable("schedule_course");

                entity.HasIndex(e => e.CourseId, "course_schedule_idx");

                entity.HasIndex(e => e.ScheduleId, "schedule_course_idx");

                entity.Property(e => e.CourseId)
                    .HasColumnType("int(11)")
                    .HasColumnName("courseID");

                entity.Property(e => e.ScheduleId)
                    .HasColumnType("int(11)")
                    .HasColumnName("scheduleID");

                entity.HasOne(d => d.Course)
                    .WithMany()
                    .HasForeignKey(d => d.CourseId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("course_schedule");

                entity.HasOne(d => d.Schedule)
                    .WithMany()
                    .HasForeignKey(d => d.ScheduleId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("schedule_course");
            });

            modelBuilder.Entity<Zoom>(entity =>
            {
                entity.ToTable("zoom");

                entity.HasIndex(e => e.CourseId, "course_zoom_idx");

                entity.Property(e => e.ZoomId)
                    .HasColumnType("int(11)")
                    .HasColumnName("zoomID");

                entity.Property(e => e.CourseId)
                    .HasColumnType("int(11)")
                    .HasColumnName("courseID");

                entity.Property(e => e.Link)
                    .HasMaxLength(150)
                    .HasColumnName("link");

                entity.Property(e => e.Password)
                    .HasMaxLength(20)
                    .HasColumnName("password");

                entity.HasOne(d => d.Course)
                    .WithMany(p => p.Zooms)
                    .HasForeignKey(d => d.CourseId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("course_zoom");
            });

            OnModelCreatingPartial(modelBuilder);
        }

        partial void OnModelCreatingPartial(ModelBuilder modelBuilder);
    }
}
