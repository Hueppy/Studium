using Microsoft.EntityFrameworkCore;
using PfotenFreunde.Shared.Models;

using Attribute = PfotenFreunde.Shared.Models.Attribute;

namespace PfotenFreunde.Shared.Contexts;

public partial class PfotenFreundeContext : DbContext
{
    public PfotenFreundeContext()
    {
    }

    public PfotenFreundeContext(DbContextOptions<PfotenFreundeContext> options)
        : base(options)
    {
    }

    public virtual DbSet<Address> Addresses { get; set; } = null!;
    public virtual DbSet<Attribute> Attributes { get; set; } = null!;
    public virtual DbSet<Chatroom> Chatrooms { get; set; } = null!;
    public virtual DbSet<Chronicle> Chronicles { get; set; } = null!;
    public virtual DbSet<FriendRequest> FriendRequests { get; set; } = null!;
    public virtual DbSet<Institution> Institutions { get; set; } = null!;
    public virtual DbSet<Login> Logins { get; set; } = null!;
    public virtual DbSet<Message> Messages { get; set; } = null!;
    public virtual DbSet<Person> People { get; set; } = null!;
    public virtual DbSet<Pet> Pets { get; set; } = null!;
    public virtual DbSet<Picture> Pictures { get; set; } = null!;
    public virtual DbSet<PicturePet> PicturePets { get; set; } = null!;
    public virtual DbSet<PicturePost> PicturePosts { get; set; } = null!;
    public virtual DbSet<PictureUser> PictureUsers { get; set; } = null!;
    public virtual DbSet<Post> Posts { get; set; } = null!;
    public virtual DbSet<Preference> Preferences { get; set; } = null!;
    public virtual DbSet<Rating> Ratings { get; set; } = null!;
    public virtual DbSet<Report> Reports { get; set; } = null!;
    public virtual DbSet<User> Users { get; set; } = null!;

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        if (!optionsBuilder.IsConfigured)
        {
            var server = Environment.GetEnvironmentVariable("DB_SERVER") ?? "localhost";
            var user = Environment.GetEnvironmentVariable("DB_USER") ?? "root";
            var password = Environment.GetEnvironmentVariable("DB_PASSWORD") ?? "example";
            var database = Environment.GetEnvironmentVariable("DB_DATABASE") ?? "pfotenfreunde";
            
            optionsBuilder.UseMySql($"server={server};user={user};password={password};database={database}", Microsoft.EntityFrameworkCore.ServerVersion.Parse("10.6.5-mariadb"));
        }
    }

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.UseCollation("utf8mb4_general_ci")
            .HasCharSet("utf8mb4");

        modelBuilder.Entity<Address>(entity =>
        {
            entity.ToTable("address");

            entity.Property(e => e.Id)
                .HasColumnType("int(11)")
                .HasColumnName("id");

            entity.Property(e => e.City)
                .HasMaxLength(60)
                .HasColumnName("city");

            entity.Property(e => e.Street)
                .HasMaxLength(50)
                .HasColumnName("street");

            entity.Property(e => e.Zip)
                .HasMaxLength(10)
                .HasColumnName("zip");
        });

        modelBuilder.Entity<Attribute>(entity =>
        {
            entity.ToTable("attribute");

            entity.HasIndex(e => e.PetId, "fk_attribute_pet");

            entity.Property(e => e.Id)
                .HasColumnType("int(11)")
                .HasColumnName("id");

            entity.Property(e => e.Name)
                .HasMaxLength(30)
                .HasColumnName("name");

            entity.Property(e => e.PetId)
                .HasColumnType("int(11)")
                .HasColumnName("pet_id");

            entity.Property(e => e.Value)
                .HasMaxLength(60)
                .HasColumnName("value");

            entity.HasOne(d => d.Pet)
                .WithMany(p => p.Attributes)
                .HasForeignKey(d => d.PetId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_attribute_pet");
        });

        modelBuilder.Entity<Chatroom>(entity =>
        {
            entity.ToTable("chatroom");

            entity.Property(e => e.Id)
                .HasColumnType("int(11)")
                .HasColumnName("id");

            entity.Property(e => e.StartedAt)
                .HasColumnType("datetime")
                .HasColumnName("started_at");

            entity.HasMany(d => d.Users)
                .WithMany(p => p.Chatrooms)
                .UsingEntity<Dictionary<string, object>>(
                    "ChatroomUser",
                    l => l.HasOne<User>().WithMany().HasForeignKey("UserId").OnDelete(DeleteBehavior.ClientSetNull).HasConstraintName("fk_chatroom_user_user"),
                    r => r.HasOne<Chatroom>().WithMany().HasForeignKey("Id").OnDelete(DeleteBehavior.ClientSetNull).HasConstraintName("fk_chatroom_user_chatroom"),
                    j =>
                    {
                        j.HasKey("Id", "UserId").HasName("PRIMARY").HasAnnotation("MySql:IndexPrefixLength", new[] { 0, 0 });

                        j.ToTable("chatroom_user");

                        j.HasIndex(new[] { "UserId" }, "fk_chatroom_user_user");

                        j.IndexerProperty<int>("Id").HasColumnType("int(11)").HasColumnName("id");

                        j.IndexerProperty<int>("UserId").HasColumnType("int(11)").HasColumnName("user_id");
                    });
        });

        modelBuilder.Entity<Chronicle>(entity =>
        {
            entity.ToTable("chronicle");

            entity.Property(e => e.Id)
                .HasColumnType("int(11)")
                .HasColumnName("id");
        });

        modelBuilder.Entity<FriendRequest>(entity =>
        {
            entity.ToTable("friend_request");

            entity.HasIndex(e => e.ReceiverId, "fk_friendrequest_receiver");

            entity.HasIndex(e => e.SenderId, "fk_friendrequest_sender");

            entity.Property(e => e.Id)
                .HasColumnType("int(11)")
                .HasColumnName("id");

            entity.Property(e => e.ReceiverId)
                .HasColumnType("int(11)")
                .HasColumnName("receiver_id");

            entity.Property(e => e.SeenAt)
                .HasColumnType("datetime")
                .HasColumnName("seen_at");

            entity.Property(e => e.SendAt)
                .HasColumnType("datetime")
                .HasColumnName("send_at");

            entity.Property(e => e.SenderId)
                .HasColumnType("int(11)")
                .HasColumnName("sender_id");

            entity.Property(e => e.State)
                .HasColumnType("int(11)")
                .HasColumnName("state");

            entity.HasOne(d => d.Receiver)
                .WithMany(p => p.FriendRequestReceivers)
                .HasForeignKey(d => d.ReceiverId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_friendrequest_receiver");

            entity.HasOne(d => d.Sender)
                .WithMany(p => p.FriendRequestSenders)
                .HasForeignKey(d => d.SenderId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_friendrequest_sender");
        });

        modelBuilder.Entity<Institution>(entity =>
        {
            entity.ToTable("institution");

            entity.Property(e => e.Homepage)
                .HasMaxLength(100)
                .HasColumnName("homepage");
        });

        modelBuilder.Entity<Login>(entity =>
        {
            entity.HasKey(e => e.Email)
                .HasName("PRIMARY");

            entity.ToTable("login");

            entity.Property(e => e.Email)
                .HasMaxLength(50)
                .HasColumnName("email");

            entity.Property(e => e.PasswordHash)
                .HasMaxLength(256)
                .HasColumnName("password_hash");

            entity.Property(e => e.Role)
                .HasColumnType("int(11)")
                .HasColumnName("role");
        });

        modelBuilder.Entity<Message>(entity =>
        {
            entity.ToTable("message");

            entity.HasIndex(e => e.ChatroomId, "fk_message_chatroom");

            entity.HasIndex(e => e.SenderId, "fk_message_user");

            entity.Property(e => e.Id)
                .HasColumnType("int(11)")
                .HasColumnName("id");

            entity.Property(e => e.ChatroomId)
                .HasColumnType("int(11)")
                .HasColumnName("chatroom_id");

            entity.Property(e => e.Text)
                .HasColumnType("text")
                .HasColumnName("message");

            entity.Property(e => e.SeenAt)
                .HasColumnType("datetime")
                .HasColumnName("seen_at");

            entity.Property(e => e.SendAt)
                .HasColumnType("datetime")
                .HasColumnName("send_at");

            entity.Property(e => e.SenderId)
                .HasColumnType("int(11)")
                .HasColumnName("sender_id");

            entity.HasOne(d => d.Chatroom)
                .WithMany(p => p.Messages)
                .HasForeignKey(d => d.ChatroomId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_message_chatroom");

            entity.HasOne(d => d.Sender)
                .WithMany(p => p.Messages)
                .HasForeignKey(d => d.SenderId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_message_user");
        });

        modelBuilder.Entity<Person>(entity =>
        {
            entity.ToTable("person");

            entity.HasIndex(e => e.InstitutionId, "fk_person_institution");

            entity.Property(e => e.Age)
                .HasColumnType("int(11)")
                .HasColumnName("age");

            entity.Property(e => e.InstitutionId)
                .HasColumnType("int(11)")
                .HasColumnName("institution_id");

            entity.Property(e => e.Sex)
                .HasMaxLength(20)
                .HasColumnName("sex");

            entity.Property(e => e.Surname)
                .HasMaxLength(50)
                .HasColumnName("surname");

            entity.HasOne(d => d.Institution)
                .WithMany(p => p.People)
                .HasForeignKey(d => d.InstitutionId)
                .HasConstraintName("fk_person_institution");
        });

        modelBuilder.Entity<Pet>(entity =>
        {
            entity.ToTable("pet");

            entity.HasIndex(e => e.OwnerId, "fk_pet_owner");

            entity.Property(e => e.Id)
                .HasColumnType("int(11)")
                .HasColumnName("id");

            entity.Property(e => e.Description)
                .HasColumnType("text")
                .HasColumnName("description");

            entity.Property(e => e.Name)
                .HasMaxLength(50)
                .HasColumnName("name");

            entity.Property(e => e.OwnerId)
                .HasColumnType("int(11)")
                .HasColumnName("owner_id");

            entity.Property(e => e.Species)
                .HasColumnType("int(11)")
                .HasColumnName("species");

            entity.HasOne(d => d.Owner)
                .WithMany(p => p.Pets)
                .HasForeignKey(d => d.OwnerId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_pet_owner");
        });

        modelBuilder.Entity<Picture>(entity =>
        {
            entity.ToTable("picture");

            entity.Property(e => e.Id)
                .HasColumnType("int(11)")
                .HasColumnName("id");

            entity.Property(e => e.Data)
                .HasColumnType("mediumblob")
                .HasColumnName("data");

            entity.Property(e => e.UploadDate)
                .HasColumnType("datetime")
                .HasColumnName("upload_date");

            entity.Property(e => e.UploaderId)
                .HasColumnType("int(11)")
                .HasColumnName("uploader_id");

            entity.HasOne(d => d.Uploader)
                .WithMany(p => p.Pictures)
                .HasForeignKey(d => d.UploaderId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_picture_user");
        });

        modelBuilder.Entity<PicturePet>(entity =>
        {
            entity.ToTable("picture_pet");

            entity.HasIndex(e => e.PetId, "fk_picture_pet_pet");

            entity.Property(e => e.Id)
                .HasColumnType("int(11)")
                .ValueGeneratedNever()
                .HasColumnName("id");

            entity.Property(e => e.PetId)
                .HasColumnType("int(11)")
                .HasColumnName("pet_id");

            entity.HasOne(d => d.Picture)
                .WithOne(p => p.PicturePet)
                .HasForeignKey<PicturePet>(d => d.Id)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_picture_pet_picture");

            entity.HasOne(d => d.Pet)
                .WithMany(p => p.PicturePets)
                .HasForeignKey(d => d.PetId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_picture_pet_pet");
        });

        modelBuilder.Entity<PicturePost>(entity =>
        {
            entity.ToTable("picture_post");

            entity.HasIndex(e => e.PostId, "fk_picture_post_post");

            entity.Property(e => e.Id)
                .HasColumnType("int(11)")
                .ValueGeneratedNever()
                .HasColumnName("id");

            entity.Property(e => e.PostId)
                .HasColumnType("int(11)")
                .HasColumnName("post_id");

            entity.HasOne(d => d.Picture)
                .WithOne(p => p.PicturePost)
                .HasForeignKey<PicturePost>(d => d.Id)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_picture_post_picture");

            entity.HasOne(d => d.Post)
                .WithMany(p => p.PicturePosts)
                .HasForeignKey(d => d.PostId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_picture_post_post");
        });

        modelBuilder.Entity<PictureUser>(entity =>
        {
            entity.ToTable("picture_user");

            entity.HasIndex(e => e.UserId, "fk_picture_user_user");

            entity.Property(e => e.Id)
                .HasColumnType("int(11)")
                .ValueGeneratedNever()
                .HasColumnName("id");

            entity.Property(e => e.UserId)
                .HasColumnType("int(11)")
                .HasColumnName("user_id");

            entity.HasOne(d => d.Picture)
                .WithOne(p => p.PictureUser)
                .HasForeignKey<PictureUser>(d => d.Id)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_picture_user_picture");

            entity.HasOne(d => d.User)
                .WithMany(p => p.PictureUsers)
                .HasForeignKey(d => d.UserId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_picture_user_user");
        });

        modelBuilder.Entity<Post>(entity =>
        {
            entity.ToTable("post");

            entity.HasIndex(e => e.ChronicleId, "fk_post_chronicle");

            entity.HasIndex(e => e.UserId, "fk_post_user");

            entity.Property(e => e.Id)
                .HasColumnType("int(11)")
                .HasColumnName("id");

            entity.Property(e => e.ChronicleId)
                .HasColumnType("int(11)")
                .HasColumnName("chronicle_id");

            entity.Property(e => e.Message)
                .HasColumnType("text")
                .HasColumnName("message");

            entity.Property(e => e.PostedAt)
                .HasColumnType("datetime")
                .HasColumnName("posted_at");

            entity.Property(e => e.UserId)
                .HasColumnType("int(11)")
                .HasColumnName("user_id");

            entity.HasOne(d => d.Chronicle)
                .WithMany(p => p.Posts)
                .HasForeignKey(d => d.ChronicleId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_post_chronicle");

            entity.HasOne(d => d.User)
                .WithMany(p => p.Posts)
                .HasForeignKey(d => d.UserId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_post_user");
        });

        modelBuilder.Entity<Preference>(entity =>
        {
            entity.ToTable("preference");

            entity.HasIndex(e => e.PetId, "fk_preference_pet");

            entity.Property(e => e.Id)
                .HasColumnType("int(11)")
                .HasColumnName("id");

            entity.Property(e => e.Name)
                .HasMaxLength(30)
                .HasColumnName("name");

            entity.Property(e => e.PetId)
                .HasColumnType("int(11)")
                .HasColumnName("pet_id");

            entity.Property(e => e.Value)
                .HasMaxLength(60)
                .HasColumnName("value");

            entity.HasOne(d => d.Pet)
                .WithMany(p => p.Preferences)
                .HasForeignKey(d => d.PetId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_preference_pet");
        });

        modelBuilder.Entity<Rating>(entity =>
        {
            entity.ToTable("rating");

            entity.HasIndex(e => e.SenderId, "fk_rating_sender");

            entity.HasIndex(e => e.UserId, "fk_rating_user");

            entity.Property(e => e.Id)
                .HasColumnType("int(11)")
                .HasColumnName("id");

            entity.Property(e => e.SenderId)
                .HasColumnType("int(11)")
                .HasColumnName("sender_id");

            entity.Property(e => e.Type)
                .HasColumnType("int(11)")
                .HasColumnName("type");

            entity.Property(e => e.UserId)
                .HasColumnType("int(11)")
                .HasColumnName("user_id");

            entity.HasOne(d => d.Sender)
                .WithMany(p => p.RatingSenders)
                .HasForeignKey(d => d.SenderId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_rating_sender");

            entity.HasOne(d => d.User)
                .WithMany(p => p.RatingUsers)
                .HasForeignKey(d => d.UserId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_rating_user");
        });

        modelBuilder.Entity<Report>(entity =>
        {
            entity.ToTable("report");

            entity.HasIndex(e => e.SenderId, "fk_report_sender");

            entity.HasIndex(e => e.UserId, "fk_report_user");

            entity.Property(e => e.Id)
                .HasColumnType("int(11)")
                .HasColumnName("id");

            entity.Property(e => e.Comment)
                .HasColumnType("text")
                .HasColumnName("comment");

            entity.Property(e => e.SendAt)
                .HasColumnType("datetime")
                .HasColumnName("send_at");

            entity.Property(e => e.SenderId)
                .HasColumnType("int(11)")
                .HasColumnName("sender_id");

            entity.Property(e => e.State)
                .HasColumnType("int(11)")
                .HasColumnName("state");

            entity.Property(e => e.Type)
                .HasColumnType("int(11)")
                .HasColumnName("type");

            entity.Property(e => e.UpdatedAt)
                .HasColumnType("datetime")
                .HasColumnName("updated_at");

            entity.Property(e => e.UserId)
                .HasColumnType("int(11)")
                .HasColumnName("user_id");

            entity.HasOne(d => d.Sender)
                .WithMany(p => p.ReportSenders)
                .HasForeignKey(d => d.SenderId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_report_sender");

            entity.HasOne(d => d.User)
                .WithMany(p => p.ReportUsers)
                .HasForeignKey(d => d.UserId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_report_user");
        });

        modelBuilder.Entity<User>(entity =>
        {
            entity.ToTable("user");

            entity.HasIndex(e => e.AddressId, "fk_user_address");

            entity.HasIndex(e => e.Email, "uc_user_login")
                .IsUnique();

            entity.Property(e => e.Id)
                .HasColumnType("int(11)")
                .HasColumnName("id");

            entity.Property(e => e.Active)
                .HasColumnType("bit(1)")
                .HasColumnName("active")
                .HasDefaultValueSql("b'1'");

            entity.Property(e => e.AddressId)
                .HasColumnType("int(11)")
                .HasColumnName("address_id");

            entity.Property(e => e.Email)
                .HasMaxLength(50)
                .HasColumnName("email");

            entity.Property(e => e.LockedUntil)
                .HasColumnType("datetime")
                .HasColumnName("locked_until");

            entity.Property(e => e.Name)
                .HasMaxLength(50)
                .HasColumnName("name");

            entity.Property(e => e.Status)
                .HasColumnType("int(11)")
                .HasColumnName("status");

            entity.Property(e => e.Telephone)
                .HasMaxLength(30)
                .HasColumnName("telephone");

            entity.HasOne(d => d.Address)
                .WithMany(p => p.Users)
                .HasForeignKey(d => d.AddressId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_user_address");

            entity.HasOne(d => d.Login)
                .WithOne(p => p.User)
                .HasForeignKey<User>(d => d.Email)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("fk_user_login");
        });

        OnModelCreatingPartial(modelBuilder);
    }

    partial void OnModelCreatingPartial(ModelBuilder modelBuilder);
}
