require 'rails_helper'

RSpec.describe SlotsController do
  describe "GET /index" do
    it "is successful when user logged in" do
        u = User.create(email: 'a@.com', password: '123456')
        sign_in(u)
        get :index
        expect(response.status).to eq(200)
    end

    it "is unsuccessful when user logged in" do
        get :index
        expect(response.status).to eq(302)
    end
  end
  

end