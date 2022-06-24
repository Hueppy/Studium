using System.Reflection;
using System.Security.Claims;
using FHGuide.Api.Handlers;
using FHGuide.Api.Services;
using FHGuide.Shared.Contexts;
using FHGuide.Shared.Models;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc.Authorization;
using Microsoft.OpenApi.Models;

using PasswordHasher = FHGuide.Shared.Services.PasswordHasher;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.

const string anyOriginPolicy = "anyOriginPolicy";

builder.Services.AddScoped<IAuthenticationService, AuthenticationService>();
builder.Services.AddScoped<IPasswordHasher<Account>, PasswordHasher>();
builder.Services.AddScoped<IAuthenticator, Authenticator>();

builder.Services.AddAuthentication("Basic")
	.AddScheme<AuthenticationSchemeOptions, BasicAuthenticationHandler>("Basic", (o) => {});

builder.Services.AddCors(o =>
{
    o.AddPolicy(anyOriginPolicy, b =>
    {
        b.AllowAnyHeader()
         .AllowAnyMethod()
         .AllowAnyOrigin();
    });
});

builder.Services.AddControllers((c) => 
{
	var policy = new AuthorizationPolicyBuilder()
		.RequireClaim(ClaimTypes.Email)
		.Build();
	c.Filters.Add(new AuthorizeFilter(policy));
});
builder.Services.AddDbContext<FHGuideContext>();
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen(c =>
{
	c.SupportNonNullableReferenceTypes();
    
	c.AddSecurityDefinition("basic", new OpenApiSecurityScheme
	{
		Name = "Basic Authorization",
		Type = SecuritySchemeType.Http,
		Scheme = "basic",
		In = ParameterLocation.Header,
		Description = "Basic authorization header using the bearer scheme"
	});
	c.AddSecurityRequirement(new OpenApiSecurityRequirement()
	{
		{
		    new OpenApiSecurityScheme
		    {
			    Reference = new OpenApiReference
   			    {
   				    Type = ReferenceType.SecurityScheme,
				    Id = "basic"
			    }
		    },
			new string[] {}
		}
	});
    
    // Set the comments path for the Swagger JSON and UI.
    var xmlFile = $"{Assembly.GetExecutingAssembly().GetName().Name}.xml";
    var xmlPath = Path.Combine(AppContext.BaseDirectory, xmlFile);
    c.IncludeXmlComments(xmlPath);
});

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

app.UseCors(anyOriginPolicy);
//app.UseAuthorization();
app.UseAuthentication();

app.MapControllers();

app.Run();
