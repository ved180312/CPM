class UserDetailMailer < ApplicationMailer

  # Subject can be set in your I18n file at config/locales/en.yml
  # with the following lookup:
  #
  #   en.user_detail_mailer.booking_confirmation.subject
  #
  def booking_confirmation(user_detail)
    @ud= user_detail
    mail to:  user_detail.email, subject: "booked..."
  end
end
