using Microsoft.AspNetCore.Identity;
using FHGuide.Shared.Contexts;
using FHGuide.Shared.Models;

namespace FHGuide.Api.Services;

public class Authenticator : IAuthenticator
{
	private readonly FHGuideContext context;
	private readonly IPasswordHasher<Account> hasher;
	
    public Authenticator(
		FHGuideContext context,
		IPasswordHasher<Account> hasher)
    {
		this.context = context;
		this.hasher = hasher;
    }
	
	public async Task<Account> Authenticate(string email, string password)
	{
		var login = this.context.Accounts.FirstOrDefault((x) => x.Email == email);
        
        if (login == null)
		{
			return null;
		}
			
		var result = this.hasher.VerifyHashedPassword(login, login.Password, password);
		switch (result)
		{
			case PasswordVerificationResult.Success:
				return login;
			case PasswordVerificationResult.SuccessRehashNeeded:
				login.Password = hasher.HashPassword(login, password);
				context.Update(login);
				context.SaveChanges();
				return login;
			default:
				return null;
		}
	}
}
