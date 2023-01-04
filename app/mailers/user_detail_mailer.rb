# frozen_string_literal: true

# mail
class UserDetailMailer < ApplicationMailer
  # Subject can be set in your I18n file at config/locales/en.yml
  # with the following lookup:
  #
  #   en.user_detail_mailer.booking_confirmation.subject
  #
  def booking_confirmation(customer_detail, user, bool)
    @ud = customer_detail
    email = bool == 'user' ? user.email : @ud.user.email
    
    mail to: email, subject: 'Regarding Booking Confirmation'
  end
end
