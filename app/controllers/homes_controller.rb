# frozen_string_literal: true

class HomesController < ApplicationController

  def index; end

  def hello
    render json: {"message": "Thanks for booking this. Please check mail"}   
  end
  
  def cpm
    @user = User.all
  end
end
