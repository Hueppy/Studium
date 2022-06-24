using Microsoft.AspNetCore.Identity;
using PfotenFreunde.Shared.Contexts;
using PfotenFreunde.Shared.Models;

namespace PfotenFreunde.Api.Services;

public class Authenticator : IAuthenticator
{
	private readonly PfotenFreundeContext context;
	private readonly IPasswordHasher<Login> hasher;
	
    public Authenticator(
		PfotenFreundeContext context,
		IPasswordHasher<Login> hasher)
    {
		this.context = context;
		this.hasher = hasher;
    }
	
	public async Task<Login> Authenticate(string email, string password)
	{
		var login = await this.context.Logins.FindAsync(email);
        
        if (login == null)
		{
			return null;
		}
			
		var result = this.hasher.VerifyHashedPassword(login, login.PasswordHash, password);
		switch (result)
		{
			case PasswordVerificationResult.Success:
				return login;
			case PasswordVerificationResult.SuccessRehashNeeded:
				login.PasswordHash = hasher.HashPassword(login, password);
				context.Update(login);
				context.SaveChanges();
				return login;
			default:
				return null;
		}
	}
}
